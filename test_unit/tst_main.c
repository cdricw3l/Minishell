/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tst_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouhadr <cbouhadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 13:17:01 by cbouhadr          #+#    #+#             */
/*   Updated: 2025/03/20 13:11:16 by cbouhadr         ###   ########.fr       */
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
    //char str[] = "cat < file1.txt | grep m > file.txt";
    
    // char str[] = "33.333 , -33.33";
    // char **buff = malloc(sizeof(char *) * 3);
    // if(!buff)
    //     return(1);
    
    // buff = ft_parse(str,0,ft_strlen(str), 1, buff, 0);

    // printf("buffer [0], %s et buffer [1] %s\n",buff[0], buff[1]);

    TEST_START;

    assert(tst_ast() == 1);

    TEST_SUCCES;
    return(0);
}