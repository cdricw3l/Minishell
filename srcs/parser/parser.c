/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouhadr <cbouhadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 10:32:32 by cbouhadr          #+#    #+#             */
/*   Updated: 2025/03/17 11:25:34 by cbouhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int ft_read_line(char *str)
{
    char *line;

    while (1)
    {
        line = readline(str);
        if(!line)
            return(1);
        printf("voici line %s\n", line);
    }
    return(0);
}

int ft_start_minishell(char *str)
{
    int read;

    read = ft_read_line(str);
    if(read == 1)
        return(1);
    return(0);
}