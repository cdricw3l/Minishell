/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouhadr <cbouhadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 12:30:49 by cbouhadr          #+#    #+#             */
/*   Updated: 2025/04/16 15:47:30 by cbouhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtin.h"


//  VERIFIER LE MESSAGE D'erreur pour les acces non auautorise.

static char *ft_trim_path(char *path)
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

static char	*ft_get_home_path(char *path, int cd)
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

static int ft_check_path(char *str)
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

static int ft_return_to_home(char *path)
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
// char **ft_add_variable_to_env(char **old_env, char **new_var)
// {    
//     size_t i;
//     size_t j;
//     char **new_env;
//     int env_len;
//     int idx_variable;

//     env_len = ft_get_split_len(old_env) + ft_get_split_len(new_var);
//     new_env = malloc(sizeof(char *) * (env_len + 1));
//     if(!new_env)
//         return(NULL);
//     i = 0;
//     j = 0;
//     while (i < ft_get_split_len(old_env))
//         new_env[j++] = old_env[i++];
//     i = 0;
//     while (i < ft_get_split_len(new_var))
//     {
//         /* 
//             check  if the variable is nude : exemple: export Z.
//             We need change the variable format: Z=''. 
//             or Z= ---> Z=''
//         */

//         if(ft_index_of_char(new_var[i],'=') == -1 || new_var[i][ft_index_of_char(new_var[i],'=') + 1] == '\0')
//         {
//             if(new_var[i][0] == '$')
//             {
//                 new_var[i] = ft_get_env_variable(old_env, new_var[i]);
//                 if(!new_var[i])
//                     continue;
//                 new_var[i] = &new_var[i][ft_index_of_char(new_var[i],'=') + 1];
//             }
//             else
//                 new_var[i] = transform_variable(new_var[i]);
//         }
                
//         // check if the new variable is already in env.
//         idx_variable = ft_is_variable_on_env(new_env, new_var[i],j);
//         if(idx_variable != -1)
//         {
//             /* 
//                 if the new variable is on env, th newest variable take place of the oldest variable.
//                 Else, the new variable is add att the end of the variable list.
//             */
//             free(new_env[idx_variable]);
//             new_env[idx_variable] = new_var[i];
//         }
//         else
//             new_env[j++] = new_var[i];
//         i++;
//     }
//     new_env[j] = NULL;
//     return(new_env);
// }