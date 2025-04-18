/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cw3l <cw3l@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:52:29 by cbouhadr          #+#    #+#             */
/*   Updated: 2025/04/11 16:29:10 by cw3l             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int is_unset_valide_variable(char *var)
{
    int i;

    i = 0;
    while (var[i])
    {
        if(!ft_isalnum(var[i]))
        {
            printf("unset: %s: invalid parameter name\n", var);
            return(0);
        }
        i++;
    }
    return(1);
}

int ft_count_unset_valide_variable(char **var)
{
    int i;
    int count;
    
    i = 0;
    count = 0;
    while (var[i])
    {
        if(is_unset_valide_variable(var[i]))
            count++;
        i++;
    }
    return(count);
}

int ft_delete_from_env(char *env, char **var)
{
    int i;
    int idx;
    i = 0;
    if(!env)
        return(-1);
    while (var[i] != NULL)
    {

        idx = ft_idx_of(env, '=');
        if(idx != -1)
            if(ft_strncmp(env, var[i], ft_strlen(var[i])) == 0)
                return(i);
        i++;
    }
    return(-1);
}

char **ft_delete_variable(char **old_env, char **del_var, int valide_variable)
{    
    size_t i;
    size_t j;
    char **new_env;
    size_t env_len;

    env_len = ft_get_split_len(old_env) - valide_variable;
    new_env = malloc(sizeof(char *) * (env_len + 1));
    if(!new_env)
        return(NULL);
    i = 0;
    j = 0;
    
    //PRINT_INT((int)ft_get_split_len(old_env) - valide_variable)
    while (i < ft_get_split_len(old_env))
    {
        if(ft_delete_from_env(old_env[i], del_var) != -1)
        {
            i++;
            continue;
        }
        else
            new_env[j++] = old_env[i++];
    }
    new_env[j] = NULL;

    return(new_env);
}

void ft_unset(char *variable, char ***envp)
{
    char **var;
    int valide_variable;
    char **new_env;
    /* 
        split the commande and check  if she had arguments.
        if not, of if split err, clean memory split and return;
    */
    var = ft_split(variable, 32);
    if(!var || ft_get_split_len(var) == 1)
    {
        ft_split_clean(&var);
        return;
    }
    /* 
        new_env size = actual size env - valide variable to delete.
    */
    valide_variable = ft_count_unset_valide_variable(&var[1]);
    new_env = ft_delete_variable(*envp, &var[1], valide_variable);
        //ft_display_env(new_env);
    if(!new_env)
    {
        free(var);
        return;
    }
    env_quick_s(new_env,ft_get_split_len(new_env),ft_str_env_cmp);
    free(*envp);
    *envp = new_env;
    ft_split_clean(&var);
    return;
}