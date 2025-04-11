/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tst_change_vriable.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouhadr <cbouhadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 08:52:59 by cw3l              #+#    #+#             */
/*   Updated: 2025/04/11 12:14:52 by cbouhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_unit.h"

int ft_idx_sof(char *str, char c)
{
    int i;

    i = 0;
    while (str[i] != '\0')
    {
        if(str[i] == c)
            return(i);
        i++;
    }
    return(-1);
}

int ft_delete_from(char *env, char **var)
{
    int i;
    int idx;

    i = 1;
    if(!env)
        return(-1);
    while (var[i] != NULL)
    {
        printf("%s\n", var[i]);
        idx = ft_idx_sof(var[i], '=');
        PRINT_INT(idx);
        if(idx != -1)
        {
            printf("start\n");
            if(ft_strncmp(env, var[i], idx - 1) == 0)
            {
                printf(" variable found %s\n", var[i]);
                return(i);
            }
        }
        i++;
    }
    return(-1);
}

int ft_strle(char *str)
{
    int i;

    i = 0;
    while(str[i])
        i++;
    return(i);
}



int main(void)
{


    char *s[] = {"unset","Z=1", "Z2=2", NULL};

    char t[] = "Z";
    assert(ft_delete_from(t,s) > 0);
    return(0);
}