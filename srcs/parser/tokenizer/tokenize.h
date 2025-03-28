/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouhadr <cbouhadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 11:52:00 by cw3l              #+#    #+#             */
/*   Updated: 2025/03/28 16:20:56 by cbouhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZE_H
#define TOKENIZE_H

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

#include "../../../include/main.h"

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

typedef struct s_token
{
    char            *string;
    int             token;
    int             precedence;
    int             asso;
    struct s_token  *parent;
    struct s_token  *right;
    struct s_token  *left;

} t_token;

t_token **ft_tokenize(char *str);
t_token *ft_new_token_node(char *str, int token);
void    ft_add_back_node(t_token **lst, t_token *node);
int     ft_is_commande(char *str);
int     ft_get_token(char *str);
int     ft_count_occurence_of_token(t_token *token_lst, int token);
int     ft_delete_token_lst(t_token **token_lst);


void    ft_display_commande_lst(t_token *token_lst);
void    ft_display_token_node_lst(t_token *token_lst);
void    ft_display_token_sequence_lst(t_token *token_lst);
void    ft_display_token_node(t_token *token_lst);

int     ft_get_precedence(int token);
int     ft_get_associativity(int token);
char    *ft_get_str_token(int token);

void    ft_token_lst_iter(t_token *token, void (*f)(t_token *token_node, int token));

#endif