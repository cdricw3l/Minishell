/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cw3l <cw3l@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 20:36:54 by cw3l              #+#    #+#             */
/*   Updated: 2025/03/25 15:49:51 by cw3l             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize.h"

int ft_delete_token_lst(t_token **token_lst)
{
    t_token *tmp;
    t_token *node;


    while (*token_lst)
    {
        tmp = (*token_lst)->right;
        node = *token_lst;
        if(node->string)
        {
            free(node->string);
            node->string = NULL;
        }
        free(node);
        *token_lst = tmp;
    }
    free(token_lst);
    token_lst = NULL;
    return(1);
    
}

t_token *ft_new_token_node(char *str, int token)
{
    t_token *token_node;

    token_node = malloc(sizeof(t_token));
    if(!token_node)
        return(NULL);
    token_node->string = ft_strdup(str);
    token_node->token = token;
    token_node->asso = 
    token_node->precedence = 
    token_node->left = NULL;
    token_node->right = NULL;
    return(token_node);
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

t_token **ft_tokenize(char *str)
{
    char    **split;
    int     token;
    int i;
    t_token **token_lst;

    split = ft_split(str, 32);
    if(!split)
        return(NULL);
    token_lst = malloc(sizeof(t_token *));
    if(!token_lst)
        return(ft_split_clean(&split));
    *token_lst = NULL;
    i = 0;
    while (split[i])
    {
        token = ft_get_token(split[i]); //get_token(*split);
        ft_add_back_node(token_lst,  ft_new_token_node(split[i], token));
        i++;
    }
    ft_split_clean(&split);
    return(token_lst);
}
