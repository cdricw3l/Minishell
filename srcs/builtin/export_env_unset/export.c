/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouhadr <cbouhadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:52:29 by cbouhadr          #+#    #+#             */
/*   Updated: 2025/04/16 15:03:30 by cbouhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtin.h"

static int ft_count_valide_variable(char **var, char **envp)
{
    int i;
    int count;

    i = 0;
    count = 0;
    if(!var)
        return (0);
    while (var[i])
    {
        if(ft_check_variable_export(var[i], envp))
            count++;
        i++;
    }
    return(i);
}

/*  if no args shell display the list of variable env */

static int  display_export_env(char ***env, char ***split_args)
{
    ft_split_clean(split_args);
    ft_print_env(*env, 1);
    return(1);
}

/* Add the variable to the variable list but before,
we need to check and count the good variable format  for the new allocation*/
        
static int add_variable_ex(char ***env, char **split_args)
{

    int valide_variable_len;
    char **new_env;
    
    valide_variable_len = ft_count_valide_variable(&split_args[1], *env);
    if(valide_variable_len)
    {
        new_env = ft_add_variable_to_env(*env, &split_args[1]);
        if(!new_env)
        {
            free(split_args);
            return(0);
        }
        free(*env);
        free(split_args);
        *env = new_env;
    }
    else
        return(0);
    return (1);
}

int ft_export(char ***env, char *args)
{
    char **split_args;

    //split commande and agrs.
    split_args = ft_split(args, 32);
    if(!(*env || !split_args))
        return(-1);
    if(!split_args[1] || ft_strncmp(split_args[1],"", 1) == 0)
        return(display_export_env(env,&split_args));
    add_variable_ex(env,split_args);
    ft_split_clean(&split_args);
    return(1);
}

