/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tst_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cw3l <cw3l@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 13:17:01 by cbouhadr          #+#    #+#             */
/*   Updated: 2025/03/19 07:11:10 by cw3l             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_unit.h"

int get_precedence(char c)
{
    if(c == 44)
        return(2);
    return(1);
}

char *ft_parse(char *str, int start, int end, int p)
{
    int i;


    i = start;

    while( i < end)
    {
        int pre = get_precedence(str[i + 1]);
        if(pre >= p)
        {
            printf("%c", str[i]);
            p = pre;
        }
        else
        {
            printf("\n");
            p = pre;
            ft_parse(str,i + 1,end, pre);
        }  
        i++;
    }
    return(NULL);
}



int main(void)
{
    int arr[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
    
    t_ast_node *racine;

    racine = ft_new_ast_node(0,'r');
    if(!racine)
        return(1);
    ft_print_ast_node_data(racine);
    create_tree(racine,1,2,1);
    ft_parcour_ast(racine);
    (void)arr;
    return(0);
}