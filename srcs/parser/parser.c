/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouhadr <cbouhadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 10:32:32 by cbouhadr          #+#    #+#             */
/*   Updated: 2025/04/17 15:33:03 by cbouhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "tokenizer/tokenize.h"





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

int ft_read_line(char *prompt, char **envp)
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

		//print_ast_start(ast_root);
        //ft_binary_tree_traversal(ast_root);
		execute_ast(ast_root,ast_root, &envp); // Execute AST!
        free(line);  // Free input line after processing
    }
    return 0;
}

int  ft_start_minishell(char *str, char **envp)
{
    int read;
    read = ft_read_line(str, envp);
    if(read == 1)
        return(1);
    return(0);
}