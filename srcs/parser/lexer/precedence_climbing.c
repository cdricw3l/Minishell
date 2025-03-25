/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precedence_climbing.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cw3l <cw3l@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 19:34:14 by cw3l              #+#    #+#             */
/*   Updated: 2025/03/24 20:20:04 by cw3l             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "precedence_climbing.h"
#include <assert.h>

int ft_get_prec(char c)
{
    if(c == '|')
        return(3);
    if(c == '<' || c == '>')
        return(2);
    else
        return(1);
}

char *ft_join(char *str, char c)
{
    int len;
    char *new_str;
    int i;

    if(!str)
        len = 1;
    else
        len = ft_strlen(str);
    i = 0;
    new_str = malloc(sizeof(char) * (len + 2));
    if(!new_str)
        return(NULL);
    if(str)
    {
        while (str[i])
        {
            new_str[i] = str[i];
            i++;
        }
    }
    new_str[i++] = c;
    new_str[i] = '\0';
    if(str)
        free(str);
    return(new_str);
    
}


void ft_climb_token(char *str, int precedence_min, int start, int end)
{
    (void)start;
    int i;
    int p;
    char *s;
    
    i = start;
    s = NULL;
    while (i < end)
    {
        p = ft_get_prec(str[i + 1]);
        if(p >= precedence_min)
        {   
            s = ft_join(s, str[i]);
        }
        else
        {
            printf("ENtre dans la recusion\n");
            if(s)
                printf("%s\n", s);
            s = NULL;
            ft_climb_token(str, p, i + 1, end);
        }
        i++;
    }
      
}




