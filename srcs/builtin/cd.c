/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouhadr <cbouhadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 12:30:49 by cbouhadr          #+#    #+#             */
/*   Updated: 2025/03/26 15:05:42 by cbouhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

char	*ft_get_home_path(char *path)
{
	char	*env;
	char	*total_path;

	env = getenv("HOME");
	if (!env)
		return (NULL);
	total_path = ft_strjoin(env, &path[1]);
	if (!total_path)
		return (NULL);
	path = total_path;
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
