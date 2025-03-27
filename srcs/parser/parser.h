/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cw3l <cw3l@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 10:31:06 by cbouhadr          #+#    #+#             */
/*   Updated: 2025/03/25 13:29:52 by cw3l             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
#define PARSER_H


#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>

#include <readline/readline.h>
#include <readline/history.h>
#include "../../include/main.h"
#include "tokenizer/tokenize.h"
#include "../exec/exec.h"

#define WORD 0
#define CMD 1
#define ARG 3
#define PIPE 4
#define REDIR_OPEN 5
#define REDIR_WRITE 6
#define REDIR_WRITE_A 7
#define DOUBLE_REDIR 8
#define HEREDOC 10
#define VAR 11

int     ft_start_minishell(char *str);
int     ft_read_line(char *str);


#endif