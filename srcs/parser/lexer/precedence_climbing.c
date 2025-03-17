/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precedence_climbing.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cw3l <cw3l@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 19:34:14 by cw3l              #+#    #+#             */
/*   Updated: 2025/03/17 21:09:28 by cw3l             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "precedence_climbing.h"

// void ft_clim_token(t_node **token_lst , char *str, int start, int end)
// {
    
// }

t_node **ft_get_token_lst(char *str)
{
    t_node **token_lst;

    printf("voici str %s\n", str);
    token_lst = malloc(sizeof(t_node *));
    if(!*token_lst)
        return(NULL);
    //ft_climb_token(token_lst,str);
    
    return(token_lst);
}