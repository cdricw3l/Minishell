/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tst_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cw3l <cw3l@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 13:17:01 by cbouhadr          #+#    #+#             */
/*   Updated: 2025/03/25 12:08:13 by cw3l             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_unit.h"

int get_precedence(char c)
{
    if(c == 44)
        return(2);
    return(1);
}


// 33.333 , -33.33

t_ast_node **ft_parse(char *str, int start, int end, int actual_precedence, t_ast_node **buff,int buff_idx)
{
    int i;
    char *b = NULL;


    if( start > end)
    {
        return(buff);
    }
    i = start;
    while(i < end && actual_precedence >= get_precedence(str[i + 1]))
    {
        b  = ft_join(b, str[i]);
        if(!b)
            printf("Error\n");
        printf("%d ", str[i + 1]);
        printf("%s\n", b);
            
        actual_precedence = get_precedence(str[i + 1]);
        i++;
    }

    t_ast_node *node = ft_new_ast_node(b,buff_idx);
    if(!node)
        return(NULL); 
    ft_parse(str,i + 2, end, actual_precedence, buff, buff_idx + 1);
    return(buff);
}



int main(void)
{

    assert(tst_tokenizer() == 1);
    char s[] = "    hello  ";

    char *t = ft_strtrim(s," ");
    printf("voici t %s\n", t);
    free(t);
    //ft_start_minishell("Mini-shell $ ");
    return(0);
}