/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environnement.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouhadr <cbouhadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:06:51 by cbouhadr          #+#    #+#             */
/*   Updated: 2025/04/16 15:00:26 by cbouhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONNEMENT_H
#define ENVIRONNEMENT_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

#include "../../parser/tokenizer/tokenize.h"

// variable tools

int     ft_check_variable_env(char **split_ars, char **envp);
int     ft_check_variable_export(char *var, char **envp);
int     ft_is_variable_on_env(char **env, char *var, int size);
int     ft_is_variable(char *str);
char    *ft_parse_env_variable(char *env_var);
char    *transform_variable(char *str);

// environnement tools

char    **ft_add_variable_to_env(char **old_env, char **new_var);
int     ft_get_var_idx_in_env(char **envp, char *var);
char    *ft_get_env_variable(char **envp, char *var);
void    ft_print_env(char **env, int sort);


//quick sort

void	env_quick_s(char **s, int end, int (*cmp)(char *, char *, size_t len)); //quick sort fonction for env.
int     ft_str_env_cmp(char *s1, char *s2, size_t n);

#endif