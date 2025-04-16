/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouhadr <cbouhadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 12:57:45 by cbouhadr          #+#    #+#             */
/*   Updated: 2025/04/16 16:42:42 by cbouhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtin.h"

char	*ft_parse_env_variable(char *env_var)
{
	char	*var;
	int		equal_idx;

	if (!env_var)
		return (NULL);
	equal_idx = ft_index_of_char(env_var, '=');
	if (equal_idx == -1)
		return (env_var);
	var = ft_substr(env_var, 0, equal_idx);
	return (var);
}

char	*transform_variable(char *str)
{
	char	*changed_variable;
	int		new_variable_len;
	char	*add;
	int		len;

	new_variable_len = ft_strlen(str) + 3;
	changed_variable = malloc(sizeof(char) * (new_variable_len + 1));
	if (!changed_variable)
		return (NULL);
	len = ft_strlen(str);
	ft_memcpy(changed_variable, str, len);
	if (ft_index_of_char(str, '=') != -1)
		add = ft_strdup("''");
	else
		add = ft_strdup("=''");
	ft_memcpy(&changed_variable[len], add, ft_strlen(add));
	free(str);
	free(add);
	return (changed_variable);
}

int	ft_is_variable(char *str)
{
	if (!str)
		return (0);
	str = ft_skip_space(str);
	if (str[0] == '$')
		return (1);
	return (0);
}
