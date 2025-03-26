/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouhadr <cbouhadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 12:30:49 by cbouhadr          #+#    #+#             */
/*   Updated: 2025/03/26 14:49:25 by cbouhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	ft_trunc_home_path(char *path)
{
	int	len;

	len = ft_strlen(path) - 1;
	while (len >= 0 && path[len] != '/')
		len--;
	path[len] = '\0';
}

char	*ft_get_home_path(char *path)
{
	char	**split;
	char	*env;
	char	*total_path;

	env = getenv("PATH");
	if (!env)
		return (NULL);
	split = ft_split(env, ':');
	if (!split)
		return (NULL);
	ft_trunc_home_path(split[0]);
	total_path = ft_strjoin(split[0], &path[1]);
	if (!total_path)
	{
		ft_split_clean(&split);
		return (NULL);
	}
	path = total_path;
	ft_split_clean(&split);
	return (total_path);
}

int	ft_cd(char *path)
{
	int		chdir_return;
	char	*total_path;

	if (path[0] == '~')
	{
		total_path = ft_get_home_path(path);
		if (!total_path)
			return (-1);
	}
	chdir_return = chdir(total_path);
	if (chdir_return == -1)
	{
		printf("cd: no such file or directory: %s\n", path);
		return (-1);
	}
	free(total_path);
	return (1);
}
