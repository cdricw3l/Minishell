/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cw3l <cw3l@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 20:36:54 by cw3l              #+#    #+#             */
/*   Updated: 2025/03/25 12:34:42 by cw3l             ###   ########.fr       */
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

int ft_is_commande(char *str)
{
    char *env;
    char **split;
    char *path;
    int acces;
    
    env = getenv("PATH");
    split = ft_split(env, ':');
    free(env);
    str = ft_strtrim(str," ");
    if(!env || !split )
         return(-1);
    while (*split)
    {
        path = ft_strjoin(*split, "/");
        path = ft_strjoin(path, str);
        acces = access(path,X_OK);
        if(acces == 0)
            return(1);
        free(*split);
        split++;
    }
    return(0);
}

int ft_get_token(char *str)
{
    
    if(ft_is_commande(str))
        return(CMD);
    return(0);
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
