/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cw3l <cw3l@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 12:29:53 by cbouhadr          #+#    #+#             */
/*   Updated: 2025/04/13 00:19:36 by cw3l             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

// env 11$1= Z=1 cas particulier $1 remplacer 

// valide format:  env $1(add nothing) Z=1
// int ft_check_env_format(char **split_ars)
// {
//     int i;

//     i = 0;
//     while (split_ars[i])
//     {
//         if(ft_index_of_char(split_ars[i],'=') == -1)
//             if(split_ars[i][0] != '$')
        
//     }
    
// }

int ft_env(char *args, char ***envp)
{
    char **var;
    
    if(!args)
        return (-1);
    var = ft_split(args, 32);
    if(!(*envp || !var))
        return(-1);
    if(!var[1] || ft_strncmp(var[1],"", 1) == 0)
    {
        /*  if no args shell display the list of variable env */
        ft_split_clean(&var);
        ft_split_print(*envp);
        return(1);
    }
    return(1);
}