/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cw3l <cw3l@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 12:29:53 by cbouhadr          #+#    #+#             */
/*   Updated: 2025/04/12 21:14:59 by cw3l             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void ft_process_echo(char **split_args, char **envp, int n, int fd)
{
    char *var;
    int i;

    i = 0;
    while (split_args[i])
    {
        if(ft_is_variable(split_args[i]))
        {
            var = ft_get_env_variable(envp,split_args[i]);
            if(var)
                split_args[i] = ft_strdup(var);
            else
                split_args[i] = NULL; 
        }
        if(split_args[i])
        {
            ft_putstr_fd(split_args[i],1);
            if(split_args[i + 1] != NULL)
                ft_putchar_fd(32,1);
        }
        i++;
    }
	if(!n)
		write(fd, "\n", 1);
}

void	ft_echo(char *str, int fd, char **envp)
{
	int	i;
	int arg;
    char **split_args;
    
	i = 1;
	arg = 0;
    if(!str || !*envp)
        return ;
	split_args = ft_split(str,32);
    if(!split_args)
        return ;
    if(ft_strncmp(split_args[i], "-n", ft_strlen_longest(split_args[i], "-n")) == 0)
    {
        arg = 1;
        i++;
    }
    ft_process_echo(&split_args[i], envp, arg, fd);
    ft_split_clean(&split_args);
}
