/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tst_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouhadr <cbouhadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 13:17:01 by cbouhadr          #+#    #+#             */
/*   Updated: 2025/03/20 09:16:56 by cbouhadr         ###   ########.fr       */
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

char **ft_parse(char *str, int start, int end, int actual_precedence, char **buff,int buff_idx)
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
            
        actual_precedence = get_precedence(str[i + 1]);
        i++;
    }

    buff[buff_idx] = b;
    printf("buffer : %d end %d\n",i, end);
    ft_parse(str,i + 2, end, actual_precedence, buff, buff_idx + 1);
    return(buff);
}



int main(void)
{
    //char str[] = "cat < file1.txt | grep m > file.txt";
    
    char str[] = "33.333 , -33.33";
    char **buff = malloc(sizeof(char *) * 3);
    if(!buff)
        return(1);
    
    buff = ft_parse(str,0,ft_strlen(str), 1, buff, 0);

    printf("buffer [0], %s et buffer [1] %s\n",buff[0], buff[1]);
    return(0);
}