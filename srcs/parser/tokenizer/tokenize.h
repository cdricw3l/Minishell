/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cw3l <cw3l@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 11:52:00 by cw3l              #+#    #+#             */
/*   Updated: 2025/03/25 11:57:30 by cw3l             ###   ########.fr       */
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

typedef struct s_token
{
    char            *string;
    int             token;
    int             precedence;
    int             asso;
    struct s_token  *right;
    struct s_token  *left;

} t_token;

t_token **ft_tokenize(char *str);
t_token *ft_new_token_node(char *str, int token);
void    ft_add_back_node(t_token **lst, t_token *node);
void    ft_display_token_lst(t_token *token_lst);
int     ft_is_commande(char *str);
int     ft_get_token(char *str);
int     ft_delete_token_lst(t_token **token_lst);
void    ft_display_commande_lst(t_token *token_lst);
void    ft_display_token_node_lst(t_token *token_lst);
void    ft_display_token_sequence_lst(t_token *token_lst);

#endif