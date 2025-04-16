/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouhadr <cbouhadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 11:02:58 by cbouhadr          #+#    #+#             */
/*   Updated: 2025/04/16 14:37:01 by cbouhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>

# include "export_env_unset/enviro.h"
#include "../../libft/libft.h"
#include "../parser/tokenizer/tokenize.h"


void	ft_pwd(t_token *node);
void	ft_echo(char *str, int fd, char **envp);
int		ft_cd(char *path);
int     ft_exit(int ret);
int     ft_export(char ***env, char *str);
int     ft_env(char *args, char ***envp);
void    ft_unset(char *variable, char ***envp);

#endif