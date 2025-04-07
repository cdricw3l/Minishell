/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cw3l <cw3l@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 10:32:32 by cbouhadr          #+#    #+#             */
/*   Updated: 2025/03/25 11:59:24 by cw3l             ###   ########.fr       */
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

        printf("Generated AST:\n");
        print_ast(ast_root, 0);  // Print AST structure
		//print_ast_simple(ast_root, 0); 
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