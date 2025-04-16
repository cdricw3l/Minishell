/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tst_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cw3l <cw3l@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:52:29 by cbouhadr          #+#    #+#             */
/*   Updated: 2025/04/12 07:53:53 by cw3l             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_unit.h"

void tst_cd(void)
{
    TEST_START;

    ft_pwd("pwd");
    assert(ft_cd(NULL) == -1);
    assert(ft_cd("cd") == 1);
    ft_cd("cd");
    //assert(ft_cd("cd ~/Documents") == 1);
    //assert(ft_cd("cd .") == 1);

    TEST_SUCCES;
}


int tst_builtin(int argc, char *envp[])
{
    (void)argc;
    (void)envp;
    
    tst_cd();

    return(1);
}