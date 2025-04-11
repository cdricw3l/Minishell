/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouhadr <cbouhadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 10:32:32 by cbouhadr          #+#    #+#             */
/*   Updated: 2025/04/07 14:46:42 by cbouhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "tokenizer/tokenize.h"


void ft_binary_tree_traversal(t_token *node)
{
    if (!node)
        return ;

    // Si associativité est 2, on traverse d'abord à droite
    if (node->asso == 2)
    {
        ft_binary_tree_traversal(node->right);  // Passe d'abord à droite
        printf("node %s asso %d\n", node->string, node->asso);
        ft_binary_tree_traversal(node->left);  // Ensuite à gauche
    }
    else
    {
        // Sinon, on suit le parcours classique (gauche - racine - droite)
        ft_binary_tree_traversal(node->left);
        printf("node %s asso %d\n", node->string, node->asso);
        ft_binary_tree_traversal(node->right);
    }
}


/* Previous version of Cedric
int ft_read_line(char *str)
{
    char *line;
    t_token **token_lst;

    while (1)
    {
        line = readline(str);
        if(!line)
            return(1);
		assert(line);
        token_lst = ft_tokenize(line);
		ft_display_token_sequence_lst(*token_lst);
		
    }
    return(0);
}
*/

int ft_read_line(char *prompt)
{
    char *line;
    t_token *ast_root;  // Now ft_tokenize returns a single AST root

    while (1)
    {
        line = readline(prompt);
        if (!line)
            return 1;

        assert(line);
		add_history(line);//permitted lib
        //ast_root = ft_tokenize(line);  // Returns AST root now
		ast_root= ft_parse(line);
        if (!ast_root)
        {
            printf("Error: Tokenization failed!\n");
            free(line);
            continue;
        }

		print_ast_start(ast_root);
        //ft_binary_tree_traversal(ast_root);
		execute_ast(ast_root); // Execute AST!
        free(line);  // Free input line after processing
    }
    return 0;
}

int  ft_start_minishell(char *str)
{
    int read;
    read = ft_read_line(str);
    if(read == 1)
        return(1);
    return(0);
}