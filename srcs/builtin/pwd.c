/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouhadr <cbouhadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 11:06:30 by cbouhadr          #+#    #+#             */
/*   Updated: 2025/03/26 12:42:55 by cbouhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

char *ft_pwd(void)
{
    /* Check for change sizeof buffer*/
    char path[1024];

    if(!getcwd(path,sizeof(path)))
    {
        // maybe change this error output.
        printf("error get path %p\n", path);
        return(NULL);
    }
    return(ft_strdup(path));
}

