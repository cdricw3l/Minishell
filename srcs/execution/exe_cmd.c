/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouhadr <cbouhadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 12:30:49 by cbouhadr          #+#    #+#             */
/*   Updated: 2025/03/28 14:02:48 by cbouhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int ft_cmd_launcher(char *path, char **args1)
{
    TEST_START;
    int pid;
    int status;
    int res;
    int b_read;
    int fd[2];
    
    pipe(fd); 
    pid = fork();
    if(pid == 0)
    {
        char bu[1024];
        close(fd[1]);
        b_read = read(fd[0],&bu,1024);
        bu[b_read] = '\0';
        close(fd[0]);
        if(ft_strncmp("hello la compagnie", bu, ft_strlen("hello la compagnie")) == 0)
        {
            if( execve(path,args1,NULL) == -1)
                return(-1);
        }
    }
    else
    {
        close(fd[0]);
        write(fd[1], "hello la compagnie", ft_strlen("hello la compagnie"));
        close(fd[1]);
        res = waitpid(pid,&status,0);
        assert(res);
        return(0);
        //printf("voici le resultat %d\n",  waitpid(pid,&status,0));
    }
    TEST_SUCCES;
    return(1);
}