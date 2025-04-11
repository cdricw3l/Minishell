/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cw3l <cw3l@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 12:29:53 by cbouhadr          #+#    #+#             */
/*   Updated: 2025/04/11 16:44:04 by cw3l             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"


// need to add the display of format $VAR

void	ft_echo(char *str, int fd)
{
	int	i;
	int arg;

	i = 0;
	arg = 0;
	while (str[i] == 32)
		i++;
	i += 4;
	while (str[i] == 32)
		i++;
	if(str[i] == '-' && str[i + 1] == 'n' && str[i + 2] == 32)
	{
		arg = 1;
		i += 3;
	}
	while (str[i])
	{
		write(fd, &str[i], 1);
		i++;
	}
	if(!arg)
		write(fd, "\n", 1);
}
