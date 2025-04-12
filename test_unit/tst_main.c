/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tst_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cw3l <cw3l@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 13:17:01 by cbouhadr          #+#    #+#             */
/*   Updated: 2025/04/12 09:26:15 by cw3l             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_unit.h"


int main(int argc, char **argv, char *envp[])
{
    TEST_START;
    (void)argv;
    (void)argc;
    (void)envp;

    //ft_sort_env(envp);
    //ft_split_quick_sort(envp, ft_get_split_len(envp),ft_strncmp);
    // ft_split_print(envp);
    //assert(tst_quick(argc, argv,envp) == 1);
    // assert(ft_is_split_sort(envp));

    //tst_quick(argc, argv,envp);
    // assert(tst_tokenizer() == 1);
    //assert(tst_export(envp) == 1);
    assert(tst_variable(envp) == 1);

    //printf("%d\n",tst_builtin(argc,envp));
    //assert(tst_exe() == 1);
    
    TEST_SUCCES;
    return(0);
}