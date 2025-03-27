/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cw3l <cw3l@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 12:30:49 by cbouhadr          #+#    #+#             */
/*   Updated: 2025/03/26 16:48:28 by cw3l             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int ft_cmd_launcher(char *path, char **args1)
{
    TEST_START;
    int pid;
    int status;
    //char *env;
    
    (void)status;
    pid = fork();
    if(pid == 0)
    {
        // env = getenv("PATH");
        // printf("ENV %s\n", env);
        TEST_START;
        // if( execve(path,args1,NULL) == -1)
        //     return(-1);
        printf("nous somme dans le fils \n");
        TEST_SUCCES;
    }
    else
    {
        sleep(5);
        printf("nous somme dans le pere \n");
        return(0);
        //printf("voici le resultat %d\n",  waitpid(pid,&status,0));
    }
    TEST_SUCCES;
    return(1);
}