/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tst_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouhadr <cbouhadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 13:17:01 by cbouhadr          #+#    #+#             */
/*   Updated: 2025/03/28 16:35:53 by cbouhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"


void    ft_print_message(int signal)
{
    printf("message reçu %d\n", signal);
}



void ft_set_signal(void)
{
    struct sigaction sa;

    sa.sa_handler = ft_print_message;
    ft_bzero(&sa, sizeof(sa));
    
    if(sigaction(SIGINT,&sa,NULL) != 0)
        perror("Err init sigaction");
    
}