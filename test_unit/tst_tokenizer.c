/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tst_tokenizer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cw3l <cw3l@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 12:07:18 by cw3l              #+#    #+#             */
/*   Updated: 2025/03/25 12:24:03 by cw3l             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_unit.h"

int tst_commande_checker(void)
{
    TEST_START;
    
    assert(ft_is_commande("      grep ff ") == 0);
    assert(ft_is_commande("      grep ") == 1);
    assert(ft_is_commande("      cat  ") == 1);
    assert(ft_is_commande("echo") == 1);
    assert(ft_is_commande("ech") == 0);
    assert(ft_is_commande("ech") == 0);
    assert(ft_is_commande("he  llo") == 0);
    assert(ft_is_commande("catgrep") == 0);
    assert(ft_is_commande("......cat.....") == 0);
    
    TEST_SUCCES;
    return(1);
}


int tst_tokenizer(void)
{
    t_token **token_lst;
    
    char line[] = "Hello grep -m | cat > output.txt"; 

    
    tst_commande_checker();
    
    token_lst = ft_tokenize(line);
    (void)token_lst;

    
    return(1);
}