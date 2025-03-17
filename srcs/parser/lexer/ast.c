/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cw3l <cw3l@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 19:56:51 by cw3l              #+#    #+#             */
/*   Updated: 2025/03/17 20:09:26 by cw3l             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "precedence_climbing.h"

t_node *ft_new_node(char value)
{
    t_node *new_node;

    new_node = malloc(sizeof(t_node));
    if(!new_node)
        return(NULL);
    new_node->value = value;
    new_node->left = NULL;
    new_node->right = NULL;

    return(new_node);
}




