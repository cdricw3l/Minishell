/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environnement_tools.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouhadr <cbouhadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:27:38 by cbouhadr          #+#    #+#             */
/*   Updated: 2025/04/16 16:25:30 by cbouhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtin.h"

int	ft_is_variable_on_env(char **env, char *var, int size)
{
	int	i;
	int	idx;

	i = 0;
	while (i < size)
	{
		idx = ft_index_of_char(env[i], '=');
		if (ft_str_env_cmp(env[i], var, idx) == 0)
			return (i);
		i++;
	}
	return (-1);
}

void	ft_print_env(char **env, int sort)
{
	char	**dup_env;

	if (!env)
		return ;
	dup_env = ft_duplicate_env(env);
	if (sort > 0)
		env_quick_s(dup_env, ft_get_split_len(dup_env), ft_str_env_cmp);
	ft_split_print(dup_env);
	ft_split_clean(&dup_env);
}

char	*ft_get_env_variable(char **envp, char *var)
{
	int	idx;

	if (!ft_is_variable(var))
		return (NULL);
	idx = ft_get_var_idx_in_env(envp, &var[1]);
	if (idx > -1)
		return (envp[idx]);
	return ("");
}

int	ft_get_var_idx_in_env(char **envp, char *var)
{
	char	*env_var;
	int		i;

	i = 0;
	while (envp[i])
	{
		env_var = ft_parse_env_variable(envp[i]);
		if (!ft_strncmp(env_var, var, ft_strlen_longest(env_var, var)))
		{
			free(env_var);
			return (i);
		}
		i++;
	}
	free(env_var);
	return (-1);
}
