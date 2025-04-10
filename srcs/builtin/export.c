/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cw3l <cw3l@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:52:29 by cbouhadr          #+#    #+#             */
/*   Updated: 2025/04/10 12:38:07 by cw3l             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"


//error message;
//bash: export: « 2x » : identifiant non valable


void ft_display_variables_list(char *envp[])
{
    while (*envp)
    {
        printf("%s\n", *envp);
        envp++;
    }
    
}

int ft_check_variable(char *var)
{
    int i;

    if(!var)
        return(0);
    i = 0;

    // first check if the first char are alpha.
    while (ft_isalpha(var[i]))
        i++;

    //  if i = 0 the first char are not alpha so the variable is incorect. 
    if(i == 0)
        return(0);
    
    // after that,only alnum are valide.
    while (var[i])
    {
        if(!ft_isalnum(var[i]) && var[i] != '=')
            return(0);
        i++;
    }
    return(1);
}

int ft_idx_of(char *str, char c)
{
    int i;

    i = 0;

    while (str[i] != '\0')
    {
        if(str[i] == c)
            return(i);
        i++;
    }
    return(-1);
}
/* fonction who check if de variable is arlready in env  before copying it */
static int ft_is_on_env(char **env, char *var, int size)
{
    int i;

    i = 0;
    while (i < size)
    {

        int idx = ft_idx_of(env[i], '=');
        if(ft_str_env_cmp(env[i], var, idx) == 0)
        {
            printf("nous najouterons pas %s comparer avec %s\n",var,  env[i]);
            return(1);
        }
        i++;
    }
    return(0);
}


char **ft_add_variable(char **old_env, char **new_var)
{    
    size_t i;
    size_t j;
    char **new_env;
    int env_len;

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
        // check if the new variable is already in env.
        if(!ft_is_on_env(new_env, new_var[i],j))
            new_env[j++] = new_var[i];
        else
        {
            //if the variable is already in env, dont forget to free the unused variable.
            free(new_var[i]);
        }
        i++;
    }
    new_env[j] = NULL;
    return(new_env);
}


int ft_count_valide_variable(char **var)
{
    int i;

    i = 0;
    if(!var)
        return(0);
    while (*var)
    {
        if(ft_check_variable(*var))
            i++;
        var++;
    }
    return(i);
}

int ft_export(char ***env, char *args)
{
    char **new_env;
    int valide_variable_len;
    char **var;

    if(!(*env))
        return(-1);
    var = ft_split(args, 32);

    if(!var[1] || ft_strncmp(var[1],"", 1) == 0)
    {
        /*  if no variable shell display the list of variable env */
        ft_display_variables_list(*env);
        return(1);
    }
    else
    {
        /* else add the variable to the variable list but before,
        we need to check and count the good variable format  for the new allocation*/
        valide_variable_len = ft_count_valide_variable(&var[1]);
        if(valide_variable_len)
        {
            new_env = ft_add_variable(*env, &var[1]);
            if(!env)
                return(0);
            free(*env);
            free(var);
            *env = new_env;
            env_quick_s(new_env,ft_get_split_len(new_env),ft_str_env_cmp);
            //ft_sort_env(*env);
        }
    }
    return(1);
}

