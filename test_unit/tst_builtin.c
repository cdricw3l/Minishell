/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tst_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cw3l <cw3l@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:52:29 by cbouhadr          #+#    #+#             */
/*   Updated: 2025/03/26 16:48:07 by cw3l             ###   ########.fr       */
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

int tst_builtin()
{



    ft_cd("/");
    ft_pwd();
    ft_cd("~/Movies");
    ft_pwd();
    //ft_start_minishell_test("Mini: ");
    // MANPATH
    // HOSTNAME
    // PATH
    // INFOPATH
    // PKG_CONFIG_PATH
    // USER
    return(1);
}