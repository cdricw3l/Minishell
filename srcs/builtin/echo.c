/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouhadr <cbouhadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 12:29:53 by cbouhadr          #+#    #+#             */
/*   Updated: 2025/03/26 12:34:47 by cbouhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void ft_echo(char *str, int fd, int option)
{
    int i;

    i = 0;
    while (str[i])
    {
        write(fd,  &str[i], 1);
        i++;
    }
    if(option == 0)
        write(fd, "\n", 1);
}
