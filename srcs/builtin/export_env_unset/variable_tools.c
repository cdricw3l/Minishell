/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouhadr <cbouhadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 12:57:45 by cbouhadr          #+#    #+#             */
/*   Updated: 2025/04/16 14:45:04 by cbouhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "enviro.h"

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

int ft_is_variable(char *str)
{
    if(!str)
        return(0);
    str = ft_skip_space(str);
    if(str[0] == '$')
        return(1);
    return(0);
}

/* fonction who check if de variable is arlready in env  before copying it */
int ft_is_variable_on_env(char **env, char *var, int size)
{
    int i;

    i = 0;
    while (i < size)
    {

        int idx = ft_idx_of(env[i], '=');
        if(ft_str_env_cmp(env[i], var, idx) == 0)
            return(i);
        i++;
    }
    return(-1);
}

int ft_check_variable_export(char *var, char **envp)
{
    int i;
    char *tmp;
    
    if(!var)
        return(0);
    i = 0;
    // first check if the first char are alpha.
    while (ft_isalpha(var[i]))
        i++;

    //  if i = 0 the first char are not alpha so the variable is incorect. 
    if(i == 0 && var[i] != '$')
        return(0);
    // $ variable treatment
    else if(i == 0 && var[i] == '$')
    {
        tmp = ft_get_env_variable(envp,var);
        if(!tmp)
            return(1);
        var = &tmp[ft_index_of_char(tmp,'=') + 1];
    }
    // after that,only alnum are valide.
    while (var[i])
    {
        if(!ft_isalnum(var[i]) && var[i] != '=')
            return(0);
        i++;
    }
    return(1);
}

int ft_check_variable_env(char **split_ars, char **envp)
{
    int i;
    char *var;

    i = 0;
    while (split_ars[i])
    {
        if(ft_index_of_char(split_ars[i],'=') == -1)
        {
            if(split_ars[i][0] != '$')
            {
                printf("env: '%s': No such file or directory\n", split_ars[i]);
                return(0);
            }
            else
            {
                var = ft_get_env_variable(envp, split_ars[i]);
                if(var)
                {
                    if(ft_index_of_char(&var[ft_index_of_char(var,'=') + 1],'=') == -1 && var[0] != '\0')
                    {
                        printf("env: '%s': No such file or diresctory\n", &var[ft_index_of_char(var,'=') + 1]);
                        return(0);
                    }
                }
                else
                    printf("here\n");
            }
        }
        i++;
    }  
    return(1);
}
