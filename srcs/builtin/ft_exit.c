/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tst_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cw3l <cw3l@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:52:29 by cbouhadr          #+#    #+#             */
/*   Updated: 2025/03/27 17:55:02 by cw3l             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int ft_exit(int ret)
{
    // extern char **environ;

    // while (*environ)
    // {
    //     if(ft_strncmp(*environ, "SYSTEMD_EXEC_PID", ft_strlen("SYSTEMD_EXEC_PID")) == 0)
    //         printf("%s\n", *environ);
    //     environ++;
    // }
    
    int fd;
    pid_t pid;
    
    ft_pwd();
    fd = open("o.txt", O_WRONLY | O_RDONLY | O_CREAT, 0644);
    if(fd < 0)
    {
        printf("error");
        return(-1);
    }
    printf("file descriptor %d\n", fd);
    dup2(fd, STDOUT_FILENO);
    dup2(0,STDOUT_FILENO);
    printf("file descriptor\n");
    
    
    
    int i = 0;
    while (1)
    {
        pid = fork();
        printf("pid %d\n", pid);
        if (pid == 0)
        {
            printf("This is the child process. (pid: %d) value %d\\n", getpid(), i);
            i+=1;    
        }
        else
        {
            printf("This is the parent process. (pid: %d), value %d\n", getpid(), i);
            i+=10;    

        }
        sleep(1);
    }
    return(ret);
}