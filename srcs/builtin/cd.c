/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cw3l <cw3l@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 12:30:49 by cbouhadr          #+#    #+#             */
/*   Updated: 2025/04/09 22:41:47 by cw3l             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

char *ft_trim_path(char *path)
{
	int i;
	int len;

	len = ft_strlen(path);
	i = 0;
	while (path[i] == 32)
		i++;
	i+=2;
	while (path[i] == 32)
		i++;
	ft_memmove(path,&path[i],len - i);
	path[len - i] = '\0';
	return(path);
}

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
	return (path);
}

int	ft_cd(char *path)
{
	int		chdir_return;
	char	*total_path;
	
	total_path = NULL;
	if(ft_strncmp(path, "cd", ft_strlen(path)) == 0)
	{
		total_path = ft_get_home_path(path);
		printf("voici %s\n", total_path);
	}
	else
	{
		path = ft_trim_path(path);
		if (path[0] == '~' )
		{
			total_path = ft_get_home_path(path);
			if (!total_path)
				return (-1);
		}
	}
	if(total_path)
	{
		chdir_return = chdir(total_path);
		free(total_path);
	}
	else
		chdir_return = chdir(path);
	if (chdir_return == -1)
	{
		printf("cd: no such file or directory: %s\n", path);
		return (-1);
	}
	return (1);
}
