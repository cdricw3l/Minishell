/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cw3l <cw3l@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 11:02:58 by cbouhadr          #+#    #+#             */
/*   Updated: 2025/04/10 12:39:28 by cw3l             ###   ########.fr       */
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
# include "../../include/main.h"

void	ft_pwd(t_token *node);
void	ft_echo(char *str, int fd);
int		ft_cd(char *path);
int     ft_exit(int ret);


// Export fonction

int     ft_export(char ***env, char *str);
int     ft_count_valide_variable(char **var);
char    **ft_add_variable(char **old_env, char **new_var);
int     ft_check_variable(char *var);
void    ft_display_variables_list(char *envp[]);
int     ft_idx_of(char *str, char c);

#endif