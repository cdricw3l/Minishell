/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cw3l <cw3l@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 12:30:49 by cbouhadr          #+#    #+#             */
/*   Updated: 2025/03/28 19:05:47 by cw3l             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int ft_cmd_launcher(t_token *token_lst)
{
    TEST_START;

    int  fds[2];
    int childen_count;
    int status;

    pid_t pid;
    pid_t res;
    
    char *arg[] = {"clear", NULL, NULL};
    childen_count = ft_count_occurence_of_token(token_lst, PIPE);
    (void)childen_count;
    pipe(fds); 
    pid = fork();
    if(pid == 0)
    {
        close(fds[1]);
        close(fds[0]);
        printf("start commande\n");
        if(execve("/usr/bin/clear",arg,NULL) == -1)
        {
            printf("Error\n");
            return(-1);
        }
    }
    else
    {
        // close(fds[1]);
        // close(fds[0]);
        res = waitpid(pid,&status,0);
        assert(res);
        return(0);
        //printf("voici le resultat %d\n",  waitpid(pid,&status,0));
    }
   TEST_SUCCES;
    return(1);
}