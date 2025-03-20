/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_instance.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouhadr <cbouhadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 19:56:51 by cw3l              #+#    #+#             */
/*   Updated: 2025/03/20 10:02:08 by cbouhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

void create_tree(t_ast_node *node,int start, int end, int idx)
{
    t_ast_node *new_node;
    
    if(start > end)
         return ;
    if(!node->left)
    {
        new_node = ft_new_ast_node("hello", 'L');
        node->left = new_node;
        node->left->parent = node;
        create_tree(node->left, start + 1, end, idx + 1);
    }
    if(!node->right)
    {
        new_node = ft_new_ast_node("hello", 'R');
        node->right = new_node;
        node->right->parent = node;
        create_tree(node->right, start + 1, end, idx + 1);
    }
    
}


t_ast_node *ft_new_ast_node(char *str, int value)
{
    t_ast_node *new_node;

    new_node = malloc(sizeof(t_ast_node));
    if(!new_node)
        return(NULL);
    new_node->value = str;
    new_node->c = value;
    new_node->parent = NULL;
    new_node->left = NULL;
    new_node->right = NULL;

    return(new_node);
}




