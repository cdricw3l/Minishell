/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_iter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouhadr <cbouhadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 14:15:47 by cbouhadr          #+#    #+#             */
/*   Updated: 2025/03/19 14:24:19 by cbouhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

void ft_count_node(t_ast_node *node, int *i)
{
    if(!node || !i)
        return ;
    (*i)++;
    ft_count_node(node->left, i);
    ft_count_node(node->right, i);
    return;
}

void ft_ast_iter(t_ast_node *node, void (*f)(t_ast_node *))
{
    if(!node)
        return ;
    f(node);
    ft_ast_iter(node->left, f);
    ft_ast_iter(node->right,f);
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