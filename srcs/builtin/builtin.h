/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouhadr <cbouhadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 11:02:58 by cbouhadr          #+#    #+#             */
/*   Updated: 2025/04/16 16:44:37 by cbouhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <signal.h>
# include <fcntl.h>
# include <unistd.h>
# include "export_env_unset/environnement.h"
# include "../../libft/libft.h"
# include "../parser/tokenizer/tokenize.h"

void	ft_pwd(char *string);
void	ft_echo(char *str, int fd, char **envp);
int		ft_cd(char *path);
int		ft_exit(t_token **first_node, int ret, char ***envp);
int		ft_env(char *args, char ***envp);
int		ft_export(char ***env, char *str);
void	ft_unset(char *variable, char ***envp);

#endif