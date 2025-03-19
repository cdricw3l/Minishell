/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouhadr <cbouhadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:51:55 by cbouhadr          #+#    #+#             */
/*   Updated: 2025/03/19 14:23:45 by cbouhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
#define AST_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "../../../../libft/libft.h"
#include "../../../../include/main.h"


#define  LEFT 0
#define RIGHT 0

typedef struct s_ast_node
{
    int value;
    char c;
    struct s_ast_node *parent;
    struct s_ast_node *right;
    struct s_ast_node *left;

} t_ast_node;

t_ast_node      *ft_new_ast_node(int value, char c);
void            ft_ast_add_node(t_ast_node *racine, t_ast_node *node_tree, int direction);
void            ft_ast_iter(t_ast_node *node, void (*f)(t_ast_node *));
void            create_tree(t_ast_node *node,int start, int end, int idx);
void            ft_count_node(t_ast_node *node, int *i);
void            ft_print_ast_node_data(t_ast_node *node);

#endif