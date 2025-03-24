/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cw3l <cw3l@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 10:31:06 by cbouhadr          #+#    #+#             */
/*   Updated: 2025/03/24 22:05:04 by cw3l             ###   ########.fr       */
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

#define CMD 1
#define ARG 3
#define PIPE 4
#define REDIR_OPEN 5
#define REDIR_WRITE 6
#define DOUB_REDIR 7
#define WORD 8
#define HEREDOC 9
#define VAR 10

typedef struct s_token
{
    int             token;
    char            *string;
    struct s_token *next;

} t_token;


int ft_start_minishell(char *str);
int ft_read_line(char *str);
t_token **ft_tokenize(char *str);
void    ft_display_token_lst(t_token *token_lst);

#endif