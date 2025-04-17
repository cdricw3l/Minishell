/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cw3l <cw3l@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:52:29 by cbouhadr          #+#    #+#             */
/*   Updated: 2025/04/17 09:25:30 by cw3l             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtin.h"

static int	ft_check_variable_export(char *var, char **envp)
{
	int		i;
	char	*tmp;

	if (!var)
		return (0);
	i = 0;
	while (ft_isalpha(var[i]))
		i++;
	if (i == 0 && var[i] != '$')
		return (0);
	else if (i == 0 && var[i] == '$')
	{
		tmp = ft_get_env_variable(envp, var);
		if (!tmp)
			return (1);
		var = &tmp[ft_index_of_char(tmp, '=') + 1];
	}
	while (var[i])
	{
		if (!ft_isalnum(var[i]) && var[i] != '=')
			return (0);
		i++;
	}
	return (1);
}

static int	ft_count_valide_variable(char **var, char **envp)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!var)
		return (0);
	while (var[i])
	{
		if (ft_check_variable_export(var[i], envp))
			count++;
		i++;
	}
	return (count);
}

static int	display_export_env(char ***env, char ***split_args)
{
	ft_split_clean(split_args);
	ft_print_env(*env, 1);
	return (1);
}

static int	add_variable_ex(char ***env, char **split_args)
{
	int		valide_variable_len;
	char	**new_env;

	valide_variable_len = ft_count_valide_variable(&split_args[1], *env);
	if (valide_variable_len)
	{
		new_env = ft_add_variable_to_env(*env, &split_args[1]);
		if (!new_env)
		{
			free(split_args);
			return (0);
		}
		free(*env);
		free(split_args);
		*env = new_env;
	}
	else
		return (0);
	return (1);
}

int	ft_export(char ***env, char *args)
{
	char	**split_args;

	split_args = ft_split(args, 32);
	if (!(*env || !split_args))
		return (-1);
	if (!split_args[1] || ft_strncmp(split_args[1], "", 1) == 0)
		return (display_export_env(env, &split_args));
	add_variable_ex(env, split_args);
	ft_split_clean(&split_args);
	return (1);
}
