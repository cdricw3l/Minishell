/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environnement.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouhadr <cbouhadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:52:29 by cbouhadr          #+#    #+#             */
/*   Updated: 2025/04/16 15:09:16 by cbouhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int ft_is_env_sort(char **split)
{
    int i;
    int j;
    int split_len;

    i = 0;
    split_len = ft_get_split_len(split);
    while (i < split_len - 1)
    {
        j = i + 1;
        if(ft_str_env_cmp(split[i], split[j], ft_strlen(split[i])) > 0)
            return(0);
        i++;
    }
    return(1);
    
}

void    ft_display_env(char **env)
{
    if(env)
    {
        while (*env)
        {
            printf("%s\n", *env);
            env++;
        }
    }
}

void *ft_destroy_env(char **envp[], int idx)
{
    int i;
    char **env;

    env = *envp;
    i = 0;
    while (i < idx)
    {
        free(*env);
        *env = NULL;
        i++;
    }
    return (NULL);
}


char **ft_duplicate_env(char *envp[])
{
    int env_len;
    char **dup_env;
    char *tmp;
    int i;

    if(!envp)
        return(NULL);
    env_len = ft_get_split_len(envp);
    dup_env = malloc(sizeof(char *) * (env_len + 1));
    if(!dup_env)
        return(NULL);
    i = 0;
    while (envp[i])
    {
        tmp = ft_strdup(envp[i]);
        if(!tmp)
            return(ft_destroy_env(&dup_env, i));
        dup_env[i] = tmp;
        i++;
    }
    dup_env[i] = NULL;
    return(dup_env);
}
