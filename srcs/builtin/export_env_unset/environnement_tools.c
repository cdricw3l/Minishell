/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environnement_tools.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouhadr <cbouhadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:27:38 by cbouhadr          #+#    #+#             */
/*   Updated: 2025/04/16 14:45:33 by cbouhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "enviro.h"

void ft_print_env(char **env, int sort)
{
    char **dup_env;

    if(!env)
        return;
    dup_env = ft_duplicate_env(env);
    if (sort > 0)
        env_quick_s(dup_env,ft_get_split_len(dup_env),ft_str_env_cmp);
    ft_split_print(dup_env);
    ft_split_clean(&dup_env);
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

char **ft_add_variable_to_env(char **old_env, char **new_var)
{    
    size_t i;
    size_t j;
    char **new_env;
    int env_len;
    int idx_variable;

    env_len = ft_get_split_len(old_env) + ft_get_split_len(new_var);
    new_env = malloc(sizeof(char *) * (env_len + 1));
    if(!new_env)
        return(NULL);
    i = 0;
    j = 0;
    while (i < ft_get_split_len(old_env))
        new_env[j++] = old_env[i++];
    i = 0;
    while (i < ft_get_split_len(new_var))
    {
        /* 
            check  if the variable is nude : exemple: export Z.
            We need change the variable format: Z=''. 
            or Z= ---> Z=''
        */

        if(ft_idx_of(new_var[i],'=') == -1 || new_var[i][ft_index_of_char(new_var[i],'=') + 1] == '\0')
        {
            if(new_var[i][0] == '$')
            {
                new_var[i] = ft_get_env_variable(old_env, new_var[i]);
                if(!new_var[i])
                    continue;
                new_var[i] = &new_var[i][ft_index_of_char(new_var[i],'=') + 1];
            }
            else
                new_var[i] = transform_variable(new_var[i]);
        }
                
        // check if the new variable is already in env.
        idx_variable = ft_is_on_env(new_env, new_var[i],j);
        if(idx_variable != -1)
        {
            /* 
                if the new variable is on env, th newest variable take place of the oldest variable.
                Else, the new variable is add att the end of the variable list.
            */
            free(new_env[idx_variable]);
            new_env[idx_variable] = new_var[i];
        }
        else
            new_env[j++] = new_var[i];
        i++;
    }
    new_env[j] = NULL;
    return(new_env);
}