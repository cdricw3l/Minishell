/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cw3l <cw3l@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 20:36:54 by cw3l              #+#    #+#             */
/*   Updated: 2025/04/12 23:26:49 by cw3l             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize.h"
#include <assert.h>

int ft_count_number_of_arg(char **split)
{
    int i;

    i = 1;
    while (split[i] && (ft_get_token(split[i])  == WORD || ft_get_token(split[i])  == VAR))
        i++;
    return(i - 1);
}

char *ft_join_cmd_and_arg(char **split)
{
    char *new_str;
    int i;

    new_str = ft_strdup(split[0]);
    i = 1;
    while (split[i] && (ft_get_token(split[i])  == WORD || ft_get_token(split[i])  == VAR))
    {
        new_str = ft_strjoin(new_str, " ");
        new_str = ft_strjoin(new_str, split[i]);
        i++;
    }
    return(new_str);
}

const char *get_token_type_string(int token_type) {
    switch (token_type) {
        case 0: return "STRING"; // Or a more specific type if you have one for filenames
        case 1: return "CMD";
        case 4: return "PIPE";
        case 5: return "INPUT_REDIRECT";
        case 6: return "OUTPUT_REDIRECT";
        case 7: return "APPEND_REDIRECT";
        case 10: return "HEREDOC (<<)";
        case 12: return "BUILTIN";
        default: return "UNKNOWN";
    }
}

void print_ast(t_token *node, int level) 
{
    if (node == NULL) {
        return;
    }

    for (int i = 0; i < level - 1; i++) {
        printf("|   ");
    }

    if (level > 0) {
        printf("|-- ");
    }

    printf("%s", get_token_type_string(node->token));
    if (node->string) {
        printf(" (%s)", node->string);
    }
    printf("\n");

    print_ast(node->left, level + 1);
    print_ast(node->right, level + 1);
}

void print_ast_start(t_token *root) 
{
    print_ast(root, 0);
}

int ft_delete_token_lst(t_token **token_lst)
{
    t_token *tmp;
    t_token *node;


    while (*token_lst)
    {
        tmp = (*token_lst)->right;
        node = *token_lst;
        if(node->string)
        {
            free(node->string);
            node->string = NULL;
        }
		
        free(node);
        *token_lst = tmp;
    }
    free(token_lst);
    token_lst = NULL;
    return(1);
    
}

t_token *ft_new_token_node(char *str, int token)
{
    t_token *token_node;

    token_node = malloc(sizeof(t_token));
    if(!token_node)
        return(NULL);
    token_node->string = ft_strdup(str);
    token_node->token = token;
    token_node->asso = ft_get_associativity(token);
    token_node->precedence = ft_get_precedence(token);
    token_node->left = NULL;
    token_node->right = NULL;
    return(token_node);
}

// Adding to the beginning is important for correct override behavior later.
void add_redirection_to_list(t_redir **list_head, int type, char *filename) {
    t_redir *new_redir = (t_redir *)malloc(sizeof(t_redir));
    if (!new_redir) {
        perror("malloc failed in add_redirection_to_list");
        // Consider more robust error handling if needed
        return;
    }
    new_redir->type = type;
    new_redir->filename = filename; // Assuming filename persists; strdup if necessary
    new_redir->next = *list_head;
    *list_head = new_redir;
}

// --- Helper Function: Apply redirections from the list ---
// Returns 0 on success, -1 on failure.
int apply_redirections(t_redir *list) {
    t_redir *current = list;

    while (current) {
        int fd = -1;
        int flags = 0;
        int target_std_fd = -1; // STDIN_FILENO or STDOUT_FILENO

        switch (current->type) {
            case 5: // INPUT REDIRECTION (<)
                flags = O_RDONLY;
                target_std_fd = STDIN_FILENO;
                break;
            case 6: // OUTPUT REDIRECTION (>)
                flags = O_WRONLY | O_CREAT | O_TRUNC;
                target_std_fd = STDOUT_FILENO;
                break;
            case 7: // APPEND REDIRECTION (>>)
                flags = O_WRONLY | O_CREAT | O_APPEND;
                target_std_fd = STDOUT_FILENO;
                break;
            default:
                fprintf(stderr, "minishell: Internal error - Unknown redirection type %d\n", current->type);
                return -1; // Indicate failure
        }

        fd = open(current->filename, flags, 0644); // Use standard permissions
        if (fd == -1) {
            perror(current->filename); // Print error related to the specific file
            return -1; // Indicate failure
        }

        // If dup2 fails, we should still report error, maybe close fd
        if (dup2(fd, target_std_fd) == -1) {
            perror("dup2 failed");
            close(fd); // Close the file descriptor we opened
            return -1; // Indicate failure
        }

        // We MUST close the original file descriptor after dup2
        close(fd);

        current = current->next; // Move to the next redirection in the list
    }
    return 0; // Indicate success
}

// --- Helper Function: Free the redirection list ---
void free_redir_list(t_redir *list) {
    t_redir *current = list;
    t_redir *next;
    while (current) {
        next = current->next;
        // free(current->filename); // Only if you used strdup earlier
        free(current);
        current = next;
    }
} 

void ft_add_back_node(t_token **lst, t_token *node)
{
    t_token *first_node;
    
    if(!lst)
        return ;
    if(!(*lst))
        *lst = node;
    else
    {
        first_node = *lst;
        while (first_node->right)
            first_node = first_node->right;
        first_node->right = node;
    }
}

t_token *ft_tokenize(char *str)
{
    char    **split;
    int     token;
    int     i;
    t_token *token_list = NULL;
    t_token *new_node = NULL;

    split = ft_split(str, 32);
    if (!split)
        return NULL;

    i = 0;
    while (split[i])
    {
        token = ft_get_token(split[i]);  // Get token type

		if (token == HEREDOC && split[i + 1]) // Handle HEREDOC
        {
            new_node = ft_new_token_node(split[i], token);
            ft_add_back_node(&token_list, new_node);

            // The delimiter is the next token
            i++;
            if (split[i])
            {
                t_token *delimiter_node = ft_new_token_node(split[i], 0); // Assuming 0 is a generic type for delimiter
                ft_add_back_node(&token_list, delimiter_node);
            }
            else
            {
                fprintf(stderr, "Error: << without a delimiter\n");
                // Handle error
            }
            i++;
            continue;
        }

        // Handle tokens that begin with a quote
        if ((split[i][0] == '"' || split[i][0] == '\'') &&
            split[i][strlen(split[i]) - 1] != split[i][0])
        {
            char quote = split[i][0];
            char *joined = strdup(split[i]);
            i++;

            // Keep joining until the closing quote is found
            while (split[i])
            {
                char *temp = joined;
                joined = malloc(strlen(temp) + strlen(split[i]) + 2); // +1 for space, +1 for \0
                sprintf(joined, "%s %s", temp, split[i]);

                free(temp);
                if (split[i][strlen(split[i]) - 1] == quote)
                    break;
                i++;
            }

            // Remove surrounding quotes
            size_t len = strlen(joined);
            if (joined[0] == quote && joined[len - 1] == quote)
            {
                joined[len - 1] = '\0';
                memmove(joined, joined + 1, len - 1); // shift left
            }

            new_node = ft_new_token_node(joined, 1); // CMD type
            free(joined);
        }
        else
        {   
            /* 
                cedric if modification: 
                get all the word after CMD token or BUILTIN token.
                
            */
            if(token == BUILTIN || token == CMD)
            {
                // If token is BUILTIN or CMD, we count the number of WORD or $VAR token after;
                int args = ft_count_number_of_arg(&split[i]);
                //and then we join the number of arg to the commande.
                char *cmd_with_arg = ft_join_cmd_and_arg(&split[i]);
                //create new node
                new_node = ft_new_token_node(cmd_with_arg, token);

                // increment by the number of arg.
                i += args;
            }
            else
                new_node = ft_new_token_node(split[i], token);
        }
        // Add to the token list
        ft_add_back_node(&token_list, new_node);
        i++;
    }
    ft_split_clean(&split);
    return token_list;  // Return the list of tokens (linked list)
}

t_token *ft_create_ast(t_token *token_list)
{
    t_token *root = NULL;
    t_token *current = NULL;
    t_token *new_node = NULL;
    t_token *delimiter_node = NULL; // To store the delimiter token

    while (token_list)
    {
        new_node = token_list;
        token_list = token_list->right;
        new_node->right = NULL;

        if (!root)
        {
            root = new_node;//If there is no root. the first one become root.
        }
        else
        {
            if (new_node->token == 10) //HEREDOC
            {
                new_node->left = current;
                if (current)
                    current->parent = new_node;
                if (token_list)
                {
                    delimiter_node = token_list;
                    token_list = token_list->right;
                    delimiter_node->right = NULL;
                    delimiter_node->left = NULL;
                    new_node->left = root;
                    if (root)
                        root->parent = new_node;
                    new_node->right = delimiter_node;
                    delimiter_node->parent = new_node;
                    root = new_node;
                    current = new_node;
                }
                else
                {
                    fprintf(stderr, "Error: << without a delimiter in AST creation\n");
                }
                current = new_node;
                continue;
            }
			else if (new_node->token == 5 || new_node->token == 6 || new_node->token == 7) // INPUT, OUTPUT, APPEND
			{
				if (root)
				{
					new_node->left = root;
					if (root)
						root->parent = new_node;

					if (token_list) // The next token should be the filename
					{
						t_token *filename_node = token_list;
						token_list = token_list->right; // Advance token_list to the token after the filename

						new_node->right = filename_node;
						filename_node->parent = new_node;
						filename_node->right = NULL; // Ensure the filename node is properly terminated
					}
					else
					{
						fprintf(stderr, "Error: Redirection without a target\n");
					}
					root = new_node;
					current = new_node;
				}
				else
				{
					fprintf(stderr, "Error: Redirection needs a command\n");
				}
				continue;
			}
            else if (new_node->token == 4) // PIPE
            {
                if (!root)
                {
                    root = new_node;
                }
                else
                {
                    new_node->left = root;
                    if (root)
                        root->parent = new_node;
                    root = new_node;
                }
                current = new_node;
                continue;
            }
            else if (new_node->precedence == 1 && current && current->precedence == 1)
            {
                char *new_str = malloc(strlen(current->string) + strlen(new_node->string) + 2);
                sprintf(new_str, "%s %s", current->string, new_node->string);
                free(current->string);
                current->string = new_str;
                free(new_node);
            }
            else if (root && new_node->precedence > root->precedence)
            {
                new_node->left = root;
                root->parent = new_node;
                root = new_node;
            }
            else if (root)
            {
                current = root;
                while (current->right)
                    current = current->right;
                current->right = new_node;
                new_node->parent = current;
            }
        }
        current = new_node;
    }

    return root;
}

/* It works well except for multiple redirection
t_token *ft_create_ast(t_token *token_list)
{
    t_token *root = NULL;
    t_token *current = NULL;
    t_token *new_node = NULL;
	t_token *delimiter_node = NULL; // To store the delimiter token

    while (token_list)
    {
        new_node = token_list;
        token_list = token_list->right;
        new_node->right = NULL;

        if (!root)
        {
            root = new_node;//If there is no root. the first one become root. 
        }
        else
        {
			if (new_node->token == 10) //HEREDOC
            {
				// The command before '<<' becomes the left child
				new_node->left = current;
				if (current)
					current->parent = new_node;

				// The delimiter is the next token
				if (token_list)
				{
					delimiter_node = token_list;
					token_list = token_list->right;
					delimiter_node->right = NULL;
					delimiter_node->left = NULL; // Ensure delimiter node has no children initially

					new_node->left = root; // The current root (command) becomes left child
					if (root)
						root->parent = new_node;
					new_node->right = delimiter_node; // Delimiter becomes right child
					delimiter_node->parent = new_node;
					root = new_node; // HEREDOC node becomes the new root
					current = new_node;
				}
				else
				{
					fprintf(stderr, "Error: << without a delimiter in AST creation\n");
					// Handle error appropriately
				}

				// The '<<' node becomes the new 'current' for subsequent operations
				current = new_node;
				continue; // Skip the default 'current' update at the end
                
            }
			else if (new_node->token == 6) // OUTPUT_REDIRECT
            {
                if (root && root->right && root->right->token == 1) // CMD
                {
                    t_token *command_node = root->right;
                    new_node->left = command_node;
                    command_node->parent = new_node;

                    // The filename is the next token in the list
                    if (token_list)
                    {
                        new_node->right = token_list;
                        token_list->parent = new_node;
                        // Move to the next token
                        token_list = token_list->right;
                    }
                    else
                    {
                        fprintf(stderr, "Error: Output redirection without a filename\n");
                        // Handle error
                    }
                    root->right = new_node;
                    new_node->parent = root;
                }
                else if (root && root->token == 1) // CMD
                {
                    new_node->left = root;
                    root->parent = new_node;
                    if (token_list)
                    {
                        new_node->right = token_list;
                        token_list->parent = new_node;
                        token_list = token_list->right;
                    }
                    else
                    {
                        fprintf(stderr, "Error: Output redirection without a filename\n");
                    }
                    root = new_node;
                }
                else
                {
                    fprintf(stderr, "Error: Output redirection needs a command\n");
                    // Handle error
                }
                continue; // Skip the default current update
            }
			else if (new_node->token == 4) // PIPE
			{
				if (!root)
				{
					root = new_node;
				}
				else
				{
					new_node->left = root;
					if (root)
						root->parent = new_node;
					root = new_node;
				}
				current = new_node;
				continue; // Move to the next token
			}
			else if (new_node->token == 7) // APPEND_REDIRECT
			{
				if (root && root->right && root->right->token == 1) // CMD
				{
					t_token *command_node = root->right;
					new_node->left = command_node;
					command_node->parent = new_node;

					// The filename is the next token in the list
					if (token_list)
					{
						new_node->right = token_list;
						token_list->parent = new_node;
						// Move to the next token
						token_list = token_list->right;
					}
					else
					{
						fprintf(stderr, "Error: Append redirection without a filename\n");
						// Handle error
					}
					root->right = new_node;
					new_node->parent = root;
				}
				else if (root && root->token == 1) // CMD
				{
					new_node->left = root;
					root->parent = new_node;
					if (token_list)
					{
						new_node->right = token_list;
						token_list->parent = new_node;
						token_list = token_list->right;
					}
					else
					{
						fprintf(stderr, "Error: Append redirection without a filename\n");
					}
					root = new_node;
				}
				else
				{
					fprintf(stderr, "Error: Append redirection needs a command\n");
					// Handle error
				}
				continue; // Skip the default current update
			}
			// Inside ft_create_ast, when processing a new_node
            else if (new_node->precedence == 1 && current && current->precedence == 1)
            {
                // Join arguments (e.g., "echo hello world")
                char *new_str = malloc(strlen(current->string) + strlen(new_node->string) + 2);
                sprintf(new_str, "%s %s", current->string, new_node->string);
                free(current->string);
                current->string = new_str;
                free(new_node);
            }
            else if (new_node->precedence > root->precedence)
            {
                new_node->left = root;
                root->parent = new_node;
                root = new_node;
            }
            else
            {
                current = root;
                while (current->right)
                    current = current->right;
                current->right = new_node;
                new_node->parent = current;
            }
        }
        current = new_node;
    }
    return root; // Return the constructed AST
}
*/

/* 3) work well. Before doing heredoc
t_token *ft_create_ast(t_token *token_list)
{
    t_token *root = NULL;
    t_token *current = NULL;
    t_token *new_node = NULL;

    while (token_list)
    {
        new_node = token_list;
        token_list = token_list->right;
        new_node->right = NULL;

        if (!root)
        {
            root = new_node;//If there is no root. the first one become root. 
        }
        else
        {
            if (new_node->precedence == 1 && current && current->precedence == 1)
            {
                // Join arguments (e.g., "echo hello world")
                char *new_str = malloc(strlen(current->string) + strlen(new_node->string) + 2);
                sprintf(new_str, "%s %s", current->string, new_node->string);
                free(current->string);
                current->string = new_str;
                free(new_node);
            }
            else if (new_node->precedence > root->precedence)
            {
                new_node->left = root;
                root->parent = new_node;
                root = new_node;
            }
            else
            {
                current = root;
                while (current->right)
                    current = current->right;
                current->right = new_node;
                new_node->parent = current;
            }
        }
        current = new_node;
    }

    return root; // Return the constructed AST
}
*/

t_token *ft_parse(char *str)
{
	t_token *token_list = ft_tokenize(str); // Step 1: Tokenize input
    if (!token_list)
    {
        printf("error\n");
        return NULL;
    }
    t_token *ast = ft_create_ast(token_list); // Step 2: Build AST from tokens
    return ast;
} 

/* 1) original codes from Cedric
t_token **ft_tokenize(char *str)
{
    TEST_START;
    char    **split;
    int     token;
    int i;
    t_token **token_lst;

    split = ft_split(str, 32);
    if(!split)
        return(NULL);
    token_lst = malloc(sizeof(t_token *));
    if(!token_lst)
        return(ft_split_clean(&split));
    *token_lst = NULL;
    i = 0;
    while (split[i])
    {
        token = ft_get_token(split[i]);
        ft_add_back_node(token_lst,  ft_new_token_node(split[i], token));
        i++;
    }
    ft_display_token_sequence_lst(*token_lst);
    ft_split_clean(&split);
    TEST_SUCCES;
    return(token_lst);
}
*/

/* 2) It works but it didn't work on "hello hello"
t_token *ft_tokenize(char *str)
{
    char    **split;
    int     token;
    int     i;
    t_token *root = NULL;
    t_token *current = NULL;
    t_token *new_node = NULL;

    split = ft_split(str, 32);
    if (!split)
        return NULL;

    i = 0;
    while (split[i])
    {
        token = ft_get_token(split[i]);  // Get token type
        new_node = ft_new_token_node(split[i], token);

        if (!root) 
        {
            root = new_node;  // First node becomes root
        }
        else 
        {
            // **Group arguments with previous command**
            if (new_node->precedence == 1 && current && current->precedence == 1)
            {
                // Merge arguments into the previous command
                char *new_str = malloc(strlen(current->string) + strlen(new_node->string) + 2);
                sprintf(new_str, "%s %s", current->string, new_node->string);//Forbidden library
				//this store "%s %s" in new_str
                free(current->string);
                current->string = new_str;
                free(new_node);
            }
            else if (new_node->precedence > root->precedence)
            {
                new_node->left = root;  // Push previous tree to the left
                root->parent = new_node;
                root = new_node;  // New root for the AST
            }
            else 
            {
                // Attach new node to the rightmost operator
                current = root;
                while (current->right) 
                    current = current->right;

                current->right = new_node;
                new_node->parent = current;
            }
        }
        current = new_node;  // Keep track of last inserted node
        i++;
    }
    ft_split_clean(&split);
    return root;  // Return the root of the AST
}
*/