/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouhadr <cbouhadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 10:50:43 by cw3l              #+#    #+#             */
/*   Updated: 2025/04/16 12:37:43 by cbouhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int ft_is_variable(char *str)
{
    if(!str)
        return(0);
    str = ft_skip_space(str);
    if(str[0] == '$')
        return(1);
    return(0);
}

char *ft_parse_env_variable(char *env_var)
{
    char *var;
    int equal_idx;

    if(!env_var)
        return(NULL);
    equal_idx = ft_index_of_char(env_var, '=');
    if(equal_idx == -1)
        return(env_var);
    var = ft_substr(env_var, 0, equal_idx);
    return(var);
}

int ft_get_var_idx_in_env(char **envp, char *var)
{
    char *env_var;
    int i;

    i = 0;
    while (envp[i])
    {
        env_var = ft_parse_env_variable(envp[i]);
        if(ft_strncmp(env_var,var,ft_strlen_longest(env_var,var)) == 0)
        {
            free(env_var);
            return(i);
        }
        i++;
    }
    free(env_var);
    return(-1);
}

char *ft_get_env_variable(char **envp, char *var)
{
    int idx;

    if(!ft_is_variable(var))
        return(NULL);
    idx = ft_get_var_idx_in_env(envp, &var[1]);
    if(idx > -1)
        return(envp[idx]);
    return("");
}