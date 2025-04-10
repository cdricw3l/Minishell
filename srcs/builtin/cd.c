/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cw3l <cw3l@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 12:30:49 by cbouhadr          #+#    #+#             */
/*   Updated: 2025/04/10 11:34:01 by cw3l             ###   ########.fr       */
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
		printf("cd: too many arguments\n");
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
	
	/* 
		first i check if the path is valide and display the specific message if not.
		valide arg: cd + 1 argument.
	*/
	if(!ft_check_path(path))
		return(-1);
	/* 
		after, i check if cd had argument. If not, we go home.
	*/
	if(ft_strncmp(path, "cd", ft_strlen(path)) == 0)
		return(ft_return_to_home(path));
	else
	{
		/* 
			We need to separate the cd command from the path and use only the path.
		*/
		path = ft_trim_path(path);
		if (path[0] == '~' )
		{
			/* 
				if the commande had argument, if the argument start by ~ , the home path is the start point.
			*/
			path = ft_get_home_path(path, 0);
		}
	}
	/* 
		follow de path. see man chdir, check the return value. Display error message if necessary.
	*/
	chdir_return = chdir(path);
	if (chdir_return == -1)
	{
		printf("cd: no such file or directory: %s\n", path);
		return (-1);
	}
	return (1);
}
