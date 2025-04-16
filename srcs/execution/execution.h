/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouhadr <cbouhadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 12:30:49 by cbouhadr          #+#    #+#             */
/*   Updated: 2025/04/16 14:47:21 by cbouhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
#define EXECUTION_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>

#include "../parser/parser.h"
#include "../parser/tokenizer/tokenize.h"

//int     ft_cmd_launcher(t_token *token);
void    ft_set_signal(void);

// environements

char    **ft_duplicate_env(char *envp[]);
int     ft_get_env_len(char *envp[]);
void    *ft_destroy_env(char **envp[], int idx);
void    ft_display_env(char **env);
int	    ft_str_env_cmp(char *s1, char *s2, size_t n);
int     ft_is_env_sort(char **split);

#endif