/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tst_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouhadr <cbouhadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 13:17:01 by cbouhadr          #+#    #+#             */
/*   Updated: 2025/03/19 16:54:01 by cbouhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_unit.h"

int get_precedence(char c)
{
    if(c == 44)
        return(2);
    return(1);
}

char *ft_parse(char *str, int start, int end, int actual_precedence, char **buff)
{
    int i;
    int next_precedence;

    i = start;
    while(i < end)
    {
        next_precedence = get_precedence(str[i + 1]);
        if(actual_precedence == next_precedence)
        {
            *buff  = ft_join(*buff, str[i]);
            if(!*buff)
                printf("Error\n");
            /* else
                printf("%s\n", *buff); */
            printf("%c\n", str[i]);
            actual_precedence = next_precedence;
        }
        else
        {
            printf("decente\n");
            actual_precedence = 1;
            ft_parse(str,i + 1, end, actual_precedence, buff);
        }  
        i++;
        printf("\n");
    }
    return(NULL);
}



int main(void)
{
    char str[] = "cat < file1.txt | grep m > file.txt";
    char *buff = NULL;
    
    ft_parse(str,0,ft_strlen(str), 1, &buff);


    return(0);
}