/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouhadr <cbouhadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 12:29:53 by cbouhadr          #+#    #+#             */
/*   Updated: 2025/04/16 14:05:08 by cbouhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "enviro.h"

/*  if no args shell display the list of variable env */

static int  display_env_env(char ***env, char ***split_args)
{
    ft_split_clean(&split_args);
    ft_print_env(*env, 1);
    return(1);
}

static int add_variable_ev(char **env, char **split_args)
{
    char **tmp_env;

    if(!ft_check_variable_env(&split_args[1],*env))
        return(0);
    tmp_env = ft_add_variable_to_env(*env, &split_args[1]);
    if(!tmp_env)
        return(0);
    else
        ft_split_print(tmp_env);
    ft_split_clean(&tmp_env);
    return(1);
}

int ft_env(char *args, char ***env)
{
    char **split_args;
    
    if(!args)
        return (-1);
    split_args = ft_split(args, 32);
    if(!(*env || !split_args))
        return(-1);
    if(!split_args[1] || ft_strncmp(split_args[1],"", 1) == 0)
        return(display_env_env(split_args,split_args));
    add_variable_ev(*env,split_args);
    ft_split_clean(&split_args);
    return(1);
}
