/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouhadr <cbouhadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:52:29 by cbouhadr          #+#    #+#             */
/*   Updated: 2025/03/28 13:58:09 by cbouhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"


int ft_exit(int ret)
{
    int pid;
    int p;

    pid = fork();
    if(pid == 0)
    {

        printf("voici i child %d\n", pid);
    }
    else
    {
        
        printf("voici i parent %d\n", pid);
    }
    waitpid(pid, &p,0);
    printf("voici la vqleur de reotur %d et %d\n", p, pid);
    return(ret);
}