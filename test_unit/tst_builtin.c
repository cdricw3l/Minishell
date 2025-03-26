/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tst_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouhadr <cbouhadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:52:29 by cbouhadr          #+#    #+#             */
/*   Updated: 2025/03/26 12:09:02 by cbouhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_unit.h"


int tst_builtin()
{
    // Test pwd builtin.
    assert(ft_pwd() != NULL);
    printf("%s\n",ft_pwd());

    ft_echo("salut la  compagnie", 0, 1);
    ft_echo("salut la  compagnie", 1, 2);
    return(1);
}