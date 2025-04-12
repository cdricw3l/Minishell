/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tst_variable.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cw3l <cw3l@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 08:52:59 by cw3l              #+#    #+#             */
/*   Updated: 2025/04/12 10:08:04 by cw3l             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_unit.h"

char *ft_skip_space(char *str)
{
    if(!str)
        return(NULL);
    while (*str == 32)
        str++;
    return(str);
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
            return(i);
        i++;
    }
    return(-1);
}

int    ft_display_variable(char **envp, char *var)
{
    int idx;

    if(!ft_is_variable(var))
        return(-1);
    idx = ft_get_var_idx_in_env(envp, &var[1]);
    printf("voici %d \n", idx);
    if(idx > -1)
        return(printf("%s\n",envp[idx]));
    return(0);
}



int tst_variable(char **envp)
{
    TEST_START;

    char str_1[] = "$ZBHB";
    char str_2[] = "      ZBHB";
    char str_3[] = "COMMAND_MODE=unix2003";
    char var[] = "$VSCODE_GIT_ASKPASS_MAIN";

    char *t1 = ft_skip_space(str_1);
    char *t2 = ft_skip_space(str_2);
    assert(ft_is_variable(t1) == 1);
    assert(ft_is_variable(t2) == 0);
    char *e = ft_parse_env_variable(str_3);
    printf("voici %s\n", e);
    env_quick_s(envp,ft_get_split_len(envp),ft_str_env_cmp);
   //ft_display_env(envp);
    PRINT_INT(ft_get_var_idx_in_env(envp, e));
    assert(ft_get_var_idx_in_env(envp, e) == 1);
    ft_display_variable(envp,var);
    free(e);
    return(1);
}