/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tst_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouhadr <cbouhadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 13:17:01 by cbouhadr          #+#    #+#             */
/*   Updated: 2025/03/26 12:57:43 by cbouhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_unit.h"


int main(int argc, char **argv, char *envp[])
{

    (void)argv;
    //assert(tst_tokenizer() == 1);
    assert(tst_builtin(argc,envp) == 1);
    

    return(0);
}