/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouhadr <cbouhadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 11:06:30 by cbouhadr          #+#    #+#             */
/*   Updated: 2025/04/17 13:33:39 by cbouhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtin.h"

int	ft_pwd(char *string)
{
	int		i;
	char	path[10240];
	int		len;

	if(!string)
		return(-1);
	len = ft_strlen(string);
	if (ft_strncmp(string, "pwd", len) != 0)
	{
		printf("pwd: too many arguments\n");
		return (-1);
	}
	if (!getcwd(path, sizeof(path)))
	{
		printf("error get path %p\n", path);
		return (-1);
	}
	i = 0;
	while (path[i])
	{
		write(1, &path[i], 1);
		i++;
	}
	write(1, "\n", 1);
	return(1);
}
