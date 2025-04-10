/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cw3l <cw3l@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 12:30:49 by cbouhadr          #+#    #+#             */
/*   Updated: 2025/04/10 10:21:25 by cw3l             ###   ########.fr       */
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

char	*ft_get_home_path(char *path, int cd)
{
	char	*env;
	char	*total_path;

	env = getenv("HOME");
	if (!env)
		return (NULL);
	if(cd == 0)
		total_path = ft_strjoin(env, &path[1]);
	else
		total_path = env;
	if (!total_path)
		return (NULL);
	return (total_path);
}

int ft_check_path(char *str)
{
	char **split;

	split = ft_split(str, 32);
	if(ft_get_split_len(split) <=2 && ft_get_split_len(split) > 0)
		return(1);
	if(ft_get_split_len(split) == 3)
		printf("cd: string not in pwd: %s\n", split[1]);
	if(ft_get_split_len(split) > 3)
		printf("cd: too many arguments");
	ft_split_clean(&split);
	return(0);
}

int ft_return_to_home(char *path)
{
	char	*home_path;
	int		chdir_return;
	
	chdir_return = 1;
	home_path = ft_get_home_path(path, 1);
	if(home_path)
		chdir_return = chdir(home_path);
	if (chdir_return == -1)
	{
		printf("cd: no such file or directory: %s\n", path);
		return (-1);
	}
	return(1);
	
}

int	ft_cd(char *path)
{
	int		chdir_return;
	char	*total_path;
	
	total_path = NULL;
	if(!ft_check_path(path))
		return(-1);
	if(ft_strncmp(path, "cd", ft_strlen(path)) == 0)
		return(ft_return_to_home(path));
	else
	{
		path = ft_trim_path(path);
		if (path[0] == '~' )
		{
			total_path = ft_get_home_path(path, 0);
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
