/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tst_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cw3l <cw3l@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:52:29 by cbouhadr          #+#    #+#             */
/*   Updated: 2025/03/27 17:55:02 by cw3l             ###   ########.fr       */
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
int tst_builtin()
{



    
    //ft_start_minishell_test("Mini: ");
    // MANPATH
    // HOSTNAME
    // PATH
    // INFOPATH
    // PKG_CONFIG_PATH
    // USER

    extern char **environ;
    // char *env;
    // env = getenv("INFOPATH");
    ft_print_envirion(environ);
    return(1);
}