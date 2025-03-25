/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cw3l <cw3l@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 15:48:49 by cw3l              #+#    #+#             */
/*   Updated: 2025/03/25 15:52:15 by cw3l             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize.h"

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

char *ft_get_total_path(char *path, char *str)
{
    char *intermediaire_path;
    char *total_path;

    intermediaire_path = ft_strjoin(path, "/");
    total_path = ft_strjoin(intermediaire_path, str);
    free(str);
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
    char *r;
    
    env = getenv("PATH");
    split = ft_split(env, ':');
    if(!env || !split)
        return(-1);
    i = 0;
    while (split[i])
    {
        r = ft_strtrim(str," ");
        total_path = ft_get_total_path(split[i], r);
        acces = access(total_path,X_OK);
        free(total_path);
        if(acces == 0)
        {
            ft_split_clean(&split);
            return(1);
        }
        i++;
    }
    ft_split_clean(&split);
    return(0);
}
int ft_get_token(char *str)
{
    if (ft_is_commande(str))
        return (CMD);
    if (ft_strlen(str) == 1 && str[0] == '|')
        return (PIPE);
    if (ft_strlen(str) == 1 && str[0] == '<')
        return (REDIR_OPEN);
    if (ft_strlen(str) == 1 && str[0] == '>')
        return (REDIR_WRITE);
    if (ft_strlen(str) == 2 && str[0] == '>' && str[1] == '>')
        return (REDIR_WRITE_A);
    if (ft_strlen(str) == 2 && str[0] == '<' && str[1] == '<')
        return (HEREDOC);
    if (ft_strlen(str) == 2 && str[0] == '&' && str[1] == '>')
        return (DOUBLE_REDIR);
    if (str[0] == '$')
        return (VAR);
    
    return (WORD);
}
