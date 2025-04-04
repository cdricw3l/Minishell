/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouhadr <cbouhadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 22:15:03 by cw3l              #+#    #+#             */
/*   Updated: 2025/04/04 15:34:05 by cbouhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #include "../include/main.h"


int main(int argc, char **argv, char *envp[])
{

    (void)argc;
    (void)argv;
    (void)envp;
    ft_pwd();
    ft_start_minishell("Mini-shell $ ");
    
    return(0);
}