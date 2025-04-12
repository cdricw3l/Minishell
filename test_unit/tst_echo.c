/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tst_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cw3l <cw3l@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 19:38:22 by cw3l              #+#    #+#             */
/*   Updated: 2025/04/12 20:51:32 by cw3l             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_unit.h"

int tst_echo(char **envp)
{
    TEST_START;
    
    //ft_display_env(envp);
    char *var = ft_strdup("export NOFLAGS=1");
    char **dup_env = ft_duplicate_env(envp);
    ft_export(&dup_env,var);
    assert(ft_is_variable("$NOFLAGS"));
    
    printf("%s\n", ft_get_env_variable(dup_env,"$NOFLAGS"));

    ft_echo("echo $NOFLAGS", 1, dup_env);
    return(1);
}