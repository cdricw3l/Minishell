/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cw3l <cw3l@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 20:36:54 by cw3l              #+#    #+#             */
/*   Updated: 2025/03/25 13:35:42 by cw3l             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize.h"

t_token *ft_new_token_node(char *str, int token)
{
    t_token *token_node;

    token_node = malloc(sizeof(t_token));
    if(!token_node)
        return(NULL);
    token_node->string = ft_strdup(str);
    token_node->token = token;
    token_node->left = NULL;
    token_node->right = NULL;
    return(token_node);
}

void    ft_display_token_lst(t_token *token_lst)
{

    while (token_lst->right)
    {
       printf("voici la valeur du noeud: \n");
       printf("string : %s\n", token_lst->string);
       printf("value : %d\n", token_lst->token);
       token_lst = token_lst->right;
       printf("\n");
    }
}

void ft_add_back_node(t_token **lst, t_token *node)
{
    t_token *first_node;
    
    if(!lst)
        return ;
    if(!(*lst))
        *lst = node;
    else
    {
        first_node = *lst;
        while (first_node->right)
            first_node = first_node->right;
        first_node->right = node;
    }
}

char *ft_get_total_path(char *path, char *str)
{
    char *intermediaire_path;
    char *total_path;

    intermediaire_path = ft_strjoin(path, "/");
    total_path = ft_strjoin(intermediaire_path, str);
    free(intermediaire_path);
    intermediaire_path = NULL;
    return(total_path);
}

int ft_is_commande(char *str)
{
    char *env;
    char **split;
    char *total_path;
    int acces;
    int i;
    
    env = getenv("PATH");
    split = ft_split(env, ':');
    str = ft_strtrim(str," ");
    if(!env || !split)
        return(-1);
    i = 0;
    while (split[i])
    {
        total_path = ft_get_total_path(split[i], str);
        acces = access(total_path,X_OK);
        if(acces == 0)
            return(1);
        free(split[i]);
        free(total_path);
        i++;
    }
    free(str);
    free(split);
    return(0);
}

int ft_get_token(char *str)
{
    
    if(ft_is_commande(str))
        return(CMD);
    if(ft_strlen(str) == 1 && str[0] == '|')
        return(PIPE);
    if(ft_strlen(str) == 1 && str[0] == '<')
        return(REDIR_OPEN);
    if(ft_strlen(str) == 1 && str[0] == '>')
        return(REDIR_WRITE);
    if(ft_strlen(str) == 2 && str[0] == '>' && str[1] == '>')
        return(REDIR_WRITE_A);
    if(ft_strlen(str) == 2 && str[0] == '<' && str[1] == '<')
        return(HEREDOC);
    if(ft_strlen(str) == 2 && str[0] == '&' && str[1] == '>')
        return(DOUBLE_REDIR);
    if(str[0] == '$')
        return(VAR);
    
    
    return(WORD);
}

t_token **ft_tokenize(char *str)
{
    char    **split;
    int     token;
    t_token **token_lst;

    split = ft_split(str, 32);
    if(!split)
        return(NULL);
    token_lst = malloc(sizeof(t_token *));
    if(!token_lst)
        return(ft_split_clean(&split));
    *token_lst = NULL;
    while (*split)
    {
        token = ft_get_token(*split); //get_token(*split);
        ft_add_back_node(token_lst,  ft_new_token_node(*split, token));
        free(*split);
        *split = NULL;
        split++;
    }
    return(token_lst);
}
