/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precedence_climbing.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cw3l <cw3l@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 19:58:58 by cw3l              #+#    #+#             */
/*   Updated: 2025/03/18 23:57:40 by cw3l             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "../../../libft/libft.h"

#ifndef AST_H
#define AST_H

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

t_ast_node      **ft_get_token_lst(char *str);
t_ast_node      *ft_new_ast_node(int value, char c);
void            ft_ast_add_node(t_ast_node *racine, t_ast_node *node_tree, int direction);
void            ft_parcour_ast(t_ast_node *node);          
#endif