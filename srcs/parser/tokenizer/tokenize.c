/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cw3l <cw3l@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 20:36:54 by cw3l              #+#    #+#             */
/*   Updated: 2025/03/25 15:49:51 by cw3l             ###   ########.fr       */
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
	printf("|-- %s (Type: %d, Precedence: %d)\n", 
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
    t_token *current_node_being_added = NULL;
    t_token *insertion_point = NULL; // Used for finding where to attach

    while (token_list != NULL)
    {
        // 1. Get the next token and detach it from the input list
        current_node_being_added = token_list;
        token_list = token_list->right; // Advance the list pointer

        // Reset the node's links to prepare it for insertion into the AST
        current_node_being_added->right = NULL;
        current_node_being_added->left = NULL;
        current_node_being_added->parent = NULL;

        // 2. If the AST is empty, the current node becomes the root
        if (root == NULL)
        {
            root = current_node_being_added;
        }
        // 3. If the AST is not empty, decide where to insert
        else
        {
            // 3a. If the new node has HIGHER precedence than the current root,
            //     it becomes the new root of the tree.
            if (current_node_being_added->precedence > root->precedence)
            {
                current_node_being_added->left = root; // Old root becomes left child
                if (root != NULL) { // Should always be true here, but good practice
                   root->parent = current_node_being_added; // Set parent of old root
                }
                root = current_node_being_added; // Update root pointer
            }
            // 3b. If the new node has LOWER or EQUAL precedence,
            //     find the rightmost node and append it there.
            else
            {
                insertion_point = root;
                // Traverse to the end of the right spine
                while (insertion_point->right != NULL)
                {
                    insertion_point = insertion_point->right;
                }
                // Attach the new node as the right child of the rightmost node
                insertion_point->right = current_node_being_added;
                current_node_being_added->parent = insertion_point; // Set parent link
            }
        }
        // The 'current' variable from the original code, used for argument joining,
        // is no longer needed here.
    }

    return root; // Return the final root of the constructed AST
}

/* 3) last working code before using Gemini
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
            root = new_node;
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
        token = ft_get_token(split[i]); //get_token(*split);
        ft_add_back_node(token_lst,  ft_new_token_node(split[i], token));
        i++;
    }
    ft_split_clean(&split);
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