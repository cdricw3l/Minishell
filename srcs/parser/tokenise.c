/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenise.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cw3l <cw3l@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 20:36:54 by cw3l              #+#    #+#             */
/*   Updated: 2025/03/24 22:27:03 by cw3l             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_token *ft_new_token_node(char *str, int token)
{
    t_token *token_node;

    token_node = malloc(sizeof(t_token));
    if(!token_node)
        return(NULL);
    token_node->string = ft_strdup(str);
    token_node->token = token;
    return(token_node);
}

void    ft_display_token_lst(t_token *token_lst)
{

    while (token_lst->next)
    {
       printf("voici la valeur du noeud: \n");
       printf("string : %s\n", token_lst->string);
       printf("value : %d\n", token_lst->token);
       token_lst = token_lst->next;
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
        while (first_node->next)
            first_node = first_node->next;
        first_node->next = node;
    }
}

int ft_get_token(char *str)
{
    char *arg[3] = {"echo","hello", NULL};
    
    int i = execv("/bin/edcho", arg);

    printf("voici i %d\n", i);
    printf("%zu", ft_strlen(str));
    while (*str)
    {
        str++;
    }
    printf("\n");
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
