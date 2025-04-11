/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tst_change_vriable.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cw3l <cw3l@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 08:52:59 by cw3l              #+#    #+#             */
/*   Updated: 2025/04/11 09:10:24 by cw3l             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_unit.h"

int ft_strle(char *str)
{
    int i;

    i = 0;
    while(str[i])
        i++;
    return(i);
}


void tst_add_equal(void)
{
    
    char *str = strdup("Z");

    char *var = ft_add_equal(str);
    printf("voici la transformation de variable %s\n",var);
    

}

int main(void)
{
    tst_add_equal();
    return(0);
}