/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tst_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouhadr <cbouhadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:52:29 by cbouhadr          #+#    #+#             */
/*   Updated: 2025/03/28 16:17:00 by cbouhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_unit.h"

int ft_read_line_test(char *str)
{
    char *line;
    //t_token **token_lst;

    while (1)
    {
        line = readline(str);
        if(!line)
            return(1);
        // token_lst = ft_tokenize(line);
        // ft_display_token_node_lst(*token_lst);
        printf("voici line %s\n", line);
        ft_cd(line);
        ft_pwd();
    }
    return(0);
}

int ft_start_minishell_test(char *str)
{
    int read;

    read = ft_read_line_test(str);
    if(read == 1)
        return(1);
    return(0);
}
// cd ok
// pwd ok
// echo ok
//export
//unset
//exit

int ft_print_envirion(char **str)
{
    int i;

    i = 0;
    while (*str)
    {
        printf("%s\n",*str);
        str++;
        i++;
    }
    printf("\n");
    return(i);
}

void    ft_prin(void)
{
    printf("Exit\n");
}

void    ft_filter_token(t_token *token_node, int token_value)
{
    if(!token_node)
        return ;
    if(token_node->token == token_value)
    {
        ft_display_token_node(token_node);
    }
}

int tst_builtin(int argc, char *envp[])
{
    char *line;
    t_token **token_lst;

    (void)argc;
    ft_split_print(envp);
    while (1)
    {
        line = readline("minni ");
        if(!line)
            return(-1);
        token_lst = ft_tokenize(line);
        if(!token_lst)
            return(-1);
        if(ft_strncmp(line, "print",5) == 0)
            ft_display_token_node_lst(*token_lst);
        else
        {
            ft_cmd_launcher(*token_lst);
        }

    }
    
    return(1);
}