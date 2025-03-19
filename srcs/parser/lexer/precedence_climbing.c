/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precedence_climbing.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cw3l <cw3l@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 19:34:14 by cw3l              #+#    #+#             */
/*   Updated: 2025/03/19 07:12:24 by cw3l             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "precedence_climbing.h"
#include <assert.h>

int ft_get_precedence(char c)
{
    if(c == '|')
        return(3);
    if(c == '<' || c == '>')
        return(2);
    else
        return(1);
}

char *ft_join(char *str, char c)
{
    int len;
    char *new_str;
    int i;

    if(!str)
        len = 1;
    else
        len = ft_strlen(str);
    i = 0;
    new_str = malloc(sizeof(char) * (len + 2));
    if(!new_str)
        return(NULL);
    if(str)
    {
        while (str[i])
        {
            new_str[i] = str[i];
            i++;
        }
    }
    new_str[i++] = c;
    new_str[i] = '\0';
    if(str)
        free(str);
    return(new_str);
    
}


void ft_climb_token(char *str, int precedence, int start, int end)
{
    (void)start;
    int i;
    int p;
    char *s;
    
    i = start;
    s = NULL;
    while (i < end)
    {
        p = ft_get_precedence(str[i + 1]);
        if(p >= precedence)
        {   
            s = ft_join(s, str[i]);
        }
        else
        {
            printf("ENtre dans la recusion\n");
            if(s)
                printf("%s\n", s);
            s = NULL;
            ft_climb_token(str, p, i + 1, end);
        }
        i++;
    }
      
}

void create_tree(t_ast_node *node,int start, int end, int idx)
{
    t_ast_node *new_node;
    
    if(start > end)
    {
        // if(!node->left)
        // {
        //     new_node = ft_new_ast_node(idx, 'L');
        //     node->left = new_node;
        //     node->left->parent = node;
        // }
        // if(!node->right)
        // {
        //     new_node = ft_new_ast_node(idx, 'R');
        //     node->right = new_node;
        //     node->right->parent = node;
        // }
        return ;
    }
    if(!node->left)
    {
        new_node = ft_new_ast_node(idx, 'L');
        node->left = new_node;
        node->left->parent = node;
        create_tree(node->left, start + 1, end, idx + 1);
    }
    if(!node->right)
    {
        new_node = ft_new_ast_node(idx, 'R');
        node->right = new_node;
        node->right->parent = node;
        create_tree(node->right, start + 1, end, idx + 1);
    }
    
}



t_ast_node **ft_get_token_lst(char *str)
{

    t_ast_node *a;
    (void)str;
    a = ft_new_ast_node(0, 'r');
    create_tree(a,1,5,1);
    printf("dasdq %d\n", (a->right->value));
    ft_parcour_ast(a);
    
    return(0);
}