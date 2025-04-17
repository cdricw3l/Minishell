/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tst_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouhadr <cbouhadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:52:29 by cbouhadr          #+#    #+#             */
/*   Updated: 2025/04/17 13:38:50 by cbouhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_unit.h"

int tst_pwd(void)
{
    TEST_START;
    
    assert(ft_pwd("pwd fwfw") == -1);
    assert(ft_pwd("pwd") == 1);

    TEST_SUCCES;
    return(1);
}

int tst_echo(char **envp)
{
    TEST_START;
    
    char *str;

    assert(ft_echo(NULL, 1, envp) == -1);

    str = ft_strdup("echo hello world");
    assert(ft_echo(str, 1, NULL) == -1);
    free(str);
    
    str = ft_strdup("echo hello world");
    assert(ft_echo(str, 1, envp) == 1);
    free(str);

    str = ft_strdup("echo hello word ld fefq feqfeq fqefq  fvw 63364 64321\t\t cedric b fwq\n[[/;p[]\n]]");
    assert(ft_echo(str, 1, envp) == 1);
    free(str);

    str = ft_strdup("echo -n hello world");
    assert(ft_echo(str, 1, envp) == 1);
    printf("\nthe n arg for echo work \n");
    free(str);

    TEST_SUCCES;
    
    return(1);
}

int tst_cd(void)
{
    TEST_START;

    char *path;
    
    assert(ft_cd(NULL) == -1);
    path = ft_strdup("cd");
    assert(ft_cd(path) == 1);
    free(path);

    path = ft_strdup("cd ~/Documents");
    assert(ft_cd(path) == 1);
    free(path);
    
    path = ft_strdup("cd ~");
    assert(ft_cd(path) == 1);
    free(path);
    
    path = ft_strdup("cd ..");
    assert(ft_cd(path) == 1);
    free(path);

    path = ft_strdup("cd .");
    assert(ft_cd(path) == 1);
    free(path);

    path = ft_strdup("cd feqffq");
    assert(ft_cd(path) == -1);
    free(path);
    
    path = ft_strdup("cd ~/Documents fqe");
    assert(ft_cd(path) == -1);
    free(path);
    return(1);
    TEST_SUCCES;
}

int tst_builtin(int argc, char *envp[])
{
    (void)argc;
    (void)envp;
    
    assert(tst_echo(envp) == 1);
    assert(tst_cd() == 1);
    assert(tst_pwd() == 1);
    assert(tst_export(envp) == 1);

    return(1);
}