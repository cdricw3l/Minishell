/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouhadr <cbouhadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 20:36:54 by cw3l              #+#    #+#             */
/*   Updated: 2025/04/03 16:11:45 by cbouhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize.h"

void print_ast_simple(t_token *node, int indent) 
{
    if (node == NULL) 
	{
        return;
    }
    // Print node value and precedence
    for (int i = 0; i < indent; i++) printf("  ");
    printf("Node: '%s' (Prec: %d)\n", node->string ? node->string : "N/A", node->precedence);

    // Recursively print left child
    if (node->left) {
        for (int i = 0; i < indent; i++) printf("  ");
        printf(" L-> ");
        print_ast_simple(node->left, indent + 1);
    } else {
         for (int i = 0; i < indent; i++) printf("  ");
         printf(" L-> NULL\n");
    }

    // Recursively print right child
    if (node->right) {
        for (int i = 0; i < indent; i++) printf("  ");
        printf(" R-> ");
        print_ast_simple(node->right, indent + 1);
    } else {
         for (int i = 0; i < indent; i++) printf("  ");
         printf(" R-> NULL\n");
    }
}

void print_ast(t_token *node, int depth)
{
    if (!node)
        return;

    // Print current node with indentation based on depth
    for (int i = 0; i < depth; i++)
	{
        printf("    ");  // Indentation for hierarchy
	}
	printf("@-- %s (Type: %d, Precedence: %d)\n", 
		node->string ? node->string : "NULL", 
		node->token, 
		node->precedence);
    // Print left subtree first
    print_ast(node->left, depth + 1);   
    // Print right subtree after
    print_ast(node->right, depth + 1);
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
			if (new_node->token == HEREDOC)
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
        return NULL;

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