/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cw3l <cw3l@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 11:02:58 by cbouhadr          #+#    #+#             */
/*   Updated: 2025/04/12 23:36:16 by cw3l             ###   ########.fr       */
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
void	ft_echo(char *str, int fd, char **envp);
int		ft_cd(char *path);
int     ft_exit(int ret);
int     ft_export(char ***env, char *str);
int     ft_env(char *args, char ***envp);

void    ft_unset(char *variable, char ***envp);



// Export fonction

int     ft_count_valide_variable(char **var);
char    **ft_add_variable(char **old_env, char **new_var);
int     ft_check_variable(char *var);
void    ft_display_variables_list(char *envp[]);
int     ft_idx_of(char *str, char c);
int     ft_is_on_env(char **env, char *var, int size);
char    *transform_variable(char *str);

// ehco

char    *ft_get_new_arg(char *arg, char **envp);
void    ft_process_new_arg(char *new_args, char **split_arg, char **envp);
int     ft_get_new_len(char **split);
int     ft_check_arg(char *arg);

// variable $

char    *ft_get_env_variable(char **envp, char *var);
int     ft_get_var_idx_in_env(char **envp, char *var);
char     *ft_parse_env_variable(char *env_var);
int     ft_is_variable(char *str);


#endif