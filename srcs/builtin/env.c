/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouhadr <cbouhadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 12:29:53 by cbouhadr          #+#    #+#             */
/*   Updated: 2025/04/16 11:52:18 by cbouhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

// env 11$1= Z=1 cas particulier $1 remplacer 

//valide format:  env $1(add nothing) Z=1

int ft_check_env_format(char **split_ars, char **envp)
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
                    if(ft_index_of_char(&var[ft_index_of_char(var,'=') + 1],'=') == -1)
                    {
                        printf("env: '%s': No such file or diresctory\n", &var[ft_index_of_char(var,'=') + 1]);
                        return(0);
                    }
                } 
            }
        }
        i++;
    }  
    return(1);
}

int ft_env(char *args, char ***envp)
{
    char **var;
    char **tmp_env;
    
    if(!args)
        return (-1);
    var = ft_split(args, 32);
    if(!(*envp || !var))
        return(-1);
    if(!var[1] || ft_strncmp(var[1],"", 1) == 0)
    {
        /*  if no args shell display the list of variable env */
        ft_split_clean(&var);
        ft_split_print(*envp);
        return(1);
    }
    else
    {
        if(!ft_check_env_format(&var[1],*envp))
        {
            ft_split_clean(&var);
            return(1);
        }
        tmp_env = ft_add_variable(*envp, &var[1]);
        if(!tmp_env)
        {
            ft_split_clean(&var);
            return(1);
        }
        else
            ft_split_print(tmp_env);
        ft_split_clean(&tmp_env);
    }
    return(1);
}