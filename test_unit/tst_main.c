/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tst_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cw3l <cw3l@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 13:17:01 by cbouhadr          #+#    #+#             */
/*   Updated: 2025/03/19 00:33:23 by cw3l             ###   ########.fr       */
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


    printf("start %d \n", start);
    i = start;
    while (i < end)
    {
        int pre = get_precedence(str[i + 1]);
        if(str[i + 1] && pre >= p)
        {
            printf("%c", str[i]);
            p = pre;
        }
        else
        {
            printf("\n");
            p = pre;
            ft_parse(str,i + 1,end, p);
        }
        i++;
    }
    
    return(NULL);
}

int main(void)
{
    char str[] = "33.23 , -2.5";
    ft_parse(str, 1, 13, 1);


    return(0);
}