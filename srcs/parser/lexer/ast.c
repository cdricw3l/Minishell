/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cw3l <cw3l@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 19:56:51 by cw3l              #+#    #+#             */
/*   Updated: 2025/03/19 07:06:11 by cw3l             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "precedence_climbing.h"

void ft_print_ast_node_data(t_ast_node *node)
{
    if(node)
    {
        printf("\n\n####################################\n\n");
        printf("Display du node %p\n", node);
        printf("\tValue : %d\n", node->value);
        if(!node->parent)
            printf("Le noeud na pas de parent\n");
        else
            printf("Papa %p\n", node->parent);
        if(!node->left)
            printf("Le noeud na pas de fils gauche\n");
        else
            printf("fils gauche %p\n", node->left);
        if(!node->right)
            printf("Le noeud na pas de fils droit\n");
        else
            printf("fils droit %p\n", node->right);
        printf("\n\n####################################\n\n");
    }
}

void ft_parcour_ast(t_ast_node *node)
{
    if(!node)
        return ;
    ft_print_ast_node_data(node);
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
    new_node->parent = NULL;
    new_node->left = NULL;
    new_node->right = NULL;

    return(new_node);
}




