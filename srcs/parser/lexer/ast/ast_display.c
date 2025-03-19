/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_display.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouhadr <cbouhadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 14:03:48 by cbouhadr          #+#    #+#             */
/*   Updated: 2025/03/19 14:16:40 by cbouhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

void ft_print_ast_tree(t_ast_node *racine)
{
    if(racine)
    {
        ft_ast_iter(racine,ft_print_ast_node_data);
    }
}

void ft_print_ast_node_data(t_ast_node *node)
{
    if(node)
    {
        printf("\n\n####################################\n\n");
        printf("Display du node %p, %c\n", node, node->c);
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