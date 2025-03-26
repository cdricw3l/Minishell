/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouhadr <cbouhadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:51:55 by cbouhadr          #+#    #+#             */
/*   Updated: 2025/03/20 12:10:08 by cbouhadr         ###   ########.fr       */
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
    int c;
    char *value;
    struct s_ast_node *parent;
    struct s_ast_node *right;
    struct s_ast_node *left;

} t_ast_node;

t_ast_node      *ft_new_ast_node(char *str, int value);
void            ft_ast_add_node(t_ast_node **start_node, t_ast_node *new_node);
void            ft_ast_iter(t_ast_node *node, void (*f)(t_ast_node *));
void            create_tree(t_ast_node *node,int start, int end, int idx);
void            ft_count_node(t_ast_node *node, int *i);
void            ft_print_ast_node_data(t_ast_node *node);
void            ft_print_ast_tree(t_ast_node *racine);
void            ft_print_ast_value(t_ast_node *node);

#endif