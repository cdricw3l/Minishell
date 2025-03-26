/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tst_tokenizer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouhadr <cbouhadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 12:07:18 by cw3l              #+#    #+#             */
/*   Updated: 2025/03/26 09:29:32 by cbouhadr         ###   ########.fr       */
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

int tst_get_token(void)
{
    assert(ft_get_token("echo") == CMD);
    assert(ft_get_token("cat") == CMD);
    assert(ft_get_token("<<") == HEREDOC);
    assert(ft_get_token(">>") == REDIR_WRITE_A);
    assert(ft_get_token(">") == REDIR_WRITE);
    assert(ft_get_token("<") == REDIR_OPEN);
    assert(ft_get_token("&>") == DOUBLE_REDIR);
    assert(ft_get_token("$hello") == VAR);
    assert(ft_get_token("$hello") == VAR);
    assert(ft_get_token("hello") == WORD);
    
    return(1);
}


int tst_tokenizer(void)
{
    t_token **token_lst;
    
    char line[] = "Hello grep -m | cat > output.txt"; 

    
    tst_commande_checker();
    tst_get_token();
    
    token_lst = ft_tokenize(line);

    ft_display_token_node_lst(*token_lst);
    ft_display_commande_lst(*token_lst);
    ft_display_token_sequence_lst(*token_lst);
    ft_delete_token_lst(token_lst);
    
    return(1);
}