/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouhadr <cbouhadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 10:53:16 by cbouhadr          #+#    #+#             */
/*   Updated: 2025/03/20 12:15:25 by cbouhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_unit.h"

int tst_ast(void)
{

    TEST_START;
    t_ast_node *new_node_1;
    t_ast_node *new_node_2;
    t_ast_node *new_node_3;
    t_ast_node *new_node_4;
    t_ast_node *new_node_5;
    t_ast_node *new_node_6;
    t_ast_node *new_node_7;


    new_node_1 = ft_new_ast_node("Node", 124);
    new_node_2 = ft_new_ast_node("Node", 60);
    new_node_3 = ft_new_ast_node("Node", 62);
    new_node_4 = ft_new_ast_node("Node", 65);
    new_node_5 = ft_new_ast_node("Node", 66);
    new_node_6 = ft_new_ast_node("Node", 67);
    new_node_7 = ft_new_ast_node("Node", 68);

    new_node_1->left= new_node_2;
    new_node_1->right = new_node_3;
    new_node_2->left = new_node_4;
    new_node_2->right = new_node_5;
    new_node_3->left = new_node_6;
    new_node_3->right = new_node_7;

    ft_ast_iter(new_node_1, ft_print_ast_value);

    DEBUGG;

    TEST_SUCCES;
    return(1);
}