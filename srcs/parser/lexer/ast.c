/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cw3l <cw3l@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 19:56:51 by cw3l              #+#    #+#             */
/*   Updated: 2025/03/18 23:34:02 by cw3l             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "precedence_climbing.h"

void ft_parcour_ast(t_ast_node *node)
{
    if(!node)
        return ;
    printf("value node : %d in position %c poiteur %p\n", node->value, node->c,node );
    ft_parcour_ast(node->left);
    ft_parcour_ast(node->right);
}

void  ft_ast_add_node(t_ast_node *racine, t_ast_node *node_tree, int direction)
{
    
    if(racine && node_tree && (direction == LEFT || direction == RIGHT))
    {
        if(direction == LEFT)
        {
            racine->left = node_tree;
        }
        else if(direction == RIGHT)
        {
            racine->right = node_tree;
        }
    }
}

t_ast_node *ft_new_ast_node(int value, char position)
{
    t_ast_node *new_node;

    new_node = malloc(sizeof(t_ast_node));
    if(!new_node)
        return(NULL);
    new_node->value = value;
    new_node->c = position;
    new_node->left = NULL;
    new_node->right = NULL;

    return(new_node);
}




