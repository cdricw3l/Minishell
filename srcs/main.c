/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cw3l <cw3l@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 22:15:03 by cw3l              #+#    #+#             */
/*   Updated: 2025/03/24 22:21:51 by cw3l             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"


int main(void)
{
    t_token **token_lst;
    char line[] = "Hello grep -m | cat > output.txt"; 
    token_lst = ft_tokenize(line);
    (void)token_lst;
    ft_display_token_lst(*token_lst);
    //ft_start_minishell("Mini-shell $ ");
    return(0);
}