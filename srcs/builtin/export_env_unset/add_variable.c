/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_variable.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouhadr <cbouhadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:17:51 by cbouhadr          #+#    #+#             */
/*   Updated: 2025/04/17 15:51:59 by cbouhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtin.h"

static char	*process_new_variable(char **old_env, char *new_var)
{
	char	*var;

	if (ft_index_of_char(new_var, '=') == -1 || new_var[ft_index_of_char(new_var, '=') + 1] == '\0')
	{
		if (new_var[0] == '$')
		{
			var = ft_get_env_variable(old_env, new_var);
			if (!new_var)
				return (NULL);
			var = ft_strchr(var, '=') + 1;
		}
		else
			var = transform_variable(new_var);
		return (var);
	}
	return (new_var);
}

static char	**process_old_variable(char **old_env, char **new_var)
{
	size_t	i;
	size_t	j;
	int		env_len;
	char	**new_env;

	env_len = ft_get_split_len(old_env) + ft_get_split_len(new_var);
	new_env = malloc(sizeof(char *) * (env_len + 1));
	if (!new_env)
		return (NULL);
	i = 0;
	j = 0;
	while (i < ft_get_split_len(old_env))
		new_env[j++] = old_env[i++];
	return (new_env);
}

char	**ft_add_variable_to_env(char **old_env, char **new_var)
{
	size_t	i;
	size_t	j;
	char	**new_env;


	new_env = process_old_variable(old_env, new_var);
	if (!new_env)
		return (NULL);
	i = 0;
	j = 0;
	ft_split_print(new_env);
	
	while (i < ft_get_split_len(new_var))
	{
		if (process_new_variable(old_env, new_var[i]) == NULL)
		{
			i++;
			continue ;
		}
		if (ft_is_variable_on_env(new_env, new_var[i], j) != -1)
		{
			free(new_env[ft_is_variable_on_env(new_env, new_var[i], j)]);
			new_env[ft_is_variable_on_env(new_env, new_var[i], j)] = new_var[i];
		}
		else
			new_env[j++] = new_var[i];
		i++;
	}
	new_env[j] = NULL;
	return (new_env);
}
