/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_iter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouhadr <cbouhadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 14:15:47 by cbouhadr          #+#    #+#             */
/*   Updated: 2025/03/20 12:30:26 by cbouhadr         ###   ########.fr       */
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

void ft_ast_add_node(t_ast_node **start_node, t_ast_node *new_node)
{


    if(!start_node)
        return ;
    if(!*start_node)
        *start_node = new_node;
    else
    {
        if(!(*start_node)->left)
        {
            (*start_node)->left = new_node;
            (*start_node)->left->parent = *start_node;  
        }
        else if(!(*start_node)->right)
        {
            (*start_node)->right = new_node;
            (*start_node)->right->parent = *start_node;
        }
        else
        {
            ft_ast_add_node(&(*start_node)->left, new_node);
            ft_ast_add_node(&(*start_node)->right, new_node);
        }
        
    }
}

// void    ft_clean_tree(t_ast_node *node)
// {
    
// }

void ft_ast_iter(t_ast_node *node, void (*f)(t_ast_node *))
{
    if(!node)
        return ;
    if(node)
    {
        
        ft_ast_iter(node->left, f);
        if(node->c == '<')
            ft_ast_iter(node->right, f);
        ft_ast_iter(node->right, f);

        f(node);
    }
}

