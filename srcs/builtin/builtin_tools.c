/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cw3l <cw3l@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 07:23:51 by cw3l              #+#    #+#             */
/*   Updated: 2025/04/12 09:44:06 by cw3l             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

/* 
    check if token is $VAR
*/
int is_variable(char *str)
{
    if(str[0] == '$')
        return(1);
    else
        return(0);
}

char *ft_get_variable(char *var, char **env)
{
    int i;

    if(!var)
        return(NULL);
    i = 0;
    while (env[i])
    {

        int idx = ft_idx_of(env[i], '=');
        if(ft_str_env_cmp(env[i], var, idx) == 0)
            printf("Varibale found\n");
        i++;
    }
    return(NULL);
}



//Des outils de productions, des competence, des idées , une bonne equipe.