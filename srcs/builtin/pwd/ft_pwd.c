/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouhadr <cbouhadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 11:06:30 by cbouhadr          #+#    #+#             */
/*   Updated: 2025/04/16 15:59:00 by cbouhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtin.h"

void	ft_pwd(t_token *node)
{
	int		i;
	char	path[1024];
	int		len;

	len = ft_strlen(node->string);
	if (ft_strncmp(node->string, "pwd", len) != 0)
	{
		printf("pwd: too many arguments\n");
		return ;
	}
	if (!getcwd(path, sizeof(path)))
	{
		printf("error get path %p\n", path);
		return ;
	}
	i = 0;
	while (path[i])
	{
		write(1, &path[i], 1);
		i++;
	}
	write(1, "\n", 1);
}
