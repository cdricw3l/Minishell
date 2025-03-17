/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precedence_climbing.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cw3l <cw3l@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 19:34:14 by cw3l              #+#    #+#             */
/*   Updated: 2025/03/17 23:45:42 by cw3l             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "precedence_climbing.h"

int ft_get_precedence(char c)
{
    if(c == '|')
        return(3);
    if(c == '<' || c == '>')
        return(2);
    else
        return(1);
}


void ft_climb_token(t_node **token_lst , char *str, int precedence, int start, int end)
{
    (void)token_lst;
    (void)start;
    int i;
    int p;

    i = 0;

    if(start == end)
        return ;
        
    while (i < end)
    {
        p = ft_get_precedence(str[i]);
        if(p > precedence)
        {   
            precedence = p;
            ft_climb_token(token_lst, str, precedence, i, end);
            
            printf("we found value %c\n", str[i]);
        }
        i++;
    }
      
}

t_node **ft_get_token_lst(char *str)
{
    t_node **token_lst;

    printf(" %s\n", str);
    token_lst = malloc(sizeof(t_node *));
    if(!*token_lst)
        return(NULL);
    ft_climb_token(token_lst,str,1, 0, ft_strlen(str));
    
    return(token_lst);
}