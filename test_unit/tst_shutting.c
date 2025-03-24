/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tst_shutting.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cw3l <cw3l@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 13:16:38 by cbouhadr          #+#    #+#             */
/*   Updated: 2025/03/24 19:53:16 by cw3l             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_unit.h"

int ft_get_len(char *str)
{
    int i;
    int count;
    i = 0;
    count = 0;
    while (str[i])
    {
        if(str[i] != 32)
            count++;
        i++;
    }
    return(count);
}

int ft_get_p(char c)
{
    if(c == '|')
        return(2);
    if(c == '<' || c == '>')
        return(3);
    else
        return(0);
}

void ft_printf_arr(char *str, int len)
{
    int i;

    i = 0;
    if(len == 0)
        printf("Arr empty\n");
    while (i < len)
    {
        printf("%c ", str[i]);
        i++;
    }
    printf("\n");
}

int ft_push(char *str,int *len_queu, int size_max ,char c)
{
    if(*len_queu == size_max)
    {
        printf("Queu is full \n");
        return(size_max);
    }
    if(str)
    {
        str[*len_queu] = c;
        (*len_queu)++;
    }
    return(*len_queu);
}

int ft_pop(char *str, int *len)
{
    if(*len <= 0)
    {
        printf("Queu empty\n");
        return(0);
    }
    if(str)
    {
        str[*len - 1] = '\0';
        (*len)--;
    }
    return(*len);
}

char *ft_parse_str(char *str, int len)
{
    char *stack;
    char *queu;
    int len_stack;
    int len_queu;
    int i;

    stack = malloc(sizeof(char) *  (len + 1));
    if(!stack)
        return(NULL);
    queu = malloc(sizeof(char) *  (len + 1));
    if(!queu)
    {
        free(stack);
        return(NULL);
    }
    i = 0;
    len_queu = 0;
    len_stack = 0;
    while (str[i])
    {
        if(ft_get_p(str[i])  == 0)
            ft_push(queu, &len_queu,len,str[i]);
        else if (ft_get_p(str[i])  != 0)
        {
            while(ft_get_p(str[i]) > ft_get_p(stack[len_stack - 1]) && len_stack > 0)
            {
                ft_push(queu, &len_queu, len,stack[len_stack - 1]);
                ft_pop(stack, &len_stack);
                
            }
            ft_push(stack, &len_stack,len,str[i]);
            ft_printf_arr(stack, len_stack);
        }
    
        (void)len_stack;
        i++;
    }
    while (len_stack > 0)
    {
        ft_push(queu, &len_queu, len,stack[len_stack - 1]);
        ft_pop(stack, &len_stack);
    }
    queu[len_queu] = '\0';
    ft_printf_arr(queu, len_queu);

    return(queu);
    
}

int tst_shutting(void)
{
    char str[] = "cat < output.txt |  grep 'hello' > file.txt";
    int len = ft_strlen(str);

    char *pol_nnotation = ft_parse_str(str, len);
    printf("%s\n",pol_nnotation );
    
    return(1);
}