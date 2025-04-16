/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environnement_tools.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouhadr <cbouhadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:27:38 by cbouhadr          #+#    #+#             */
/*   Updated: 2025/04/16 15:46:18 by cbouhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtin.h"

// if sort = 1 env is printed sorted  else no.

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

static  char *process_new_variable(char **old_env, char *new_var)
{
    char *var;

    if(ft_index_of_char(new_var,'=') == -1 || new_var[ft_index_of_char(new_var,'=') + 1] == '\0')
    {
        if(new_var[0] == '$')
        {
            var = ft_get_env_variable(old_env, new_var);
            if(!new_var)
                return (NULL);
            var = ft_strchr(var, '=') + 1;
        }
        else
            var = transform_variable(new_var);
    }
    return(var);

}

char **process_old_variable(char **old_env,  char **new_var)
{
    int env_len;
    char **new_env;
    size_t i;
    size_t j;
    
    env_len = ft_get_split_len(old_env) + ft_get_split_len(new_var);
    new_env =  malloc(sizeof(char *) * (env_len + 1));
    if(!new_env)
        return(NULL);
    i = 0;
    j = 0;
    while (i < ft_get_split_len(old_env))
        new_env[j++] = old_env[i++];
    return(new_env);
}

char **ft_add_variable_to_env(char **old_env, char **new_var)
{    
    size_t i;
    size_t j;
    char **new_env;

    new_env = process_old_variable(old_env, new_var);
    if(!new_env)
        return(NULL);
    i = 0;
    j = 0;
    while (i < ft_get_split_len(new_var))
    {
        if(process_new_variable(old_env, new_var[i]) == NULL)
            continue;
        if(ft_is_variable_on_env(new_env, new_var[i],j) != -1)
        {
            free(new_env[ft_is_variable_on_env(new_env, new_var[i],j)]);
            new_env[ft_is_variable_on_env(new_env, new_var[i],j)] = new_var[i];
        }
        else
            new_env[j++] = new_var[i];
        i++;
    }
    new_env[j] = NULL;
    return(new_env);
}
