/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouhadr <cbouhadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 11:06:30 by cbouhadr          #+#    #+#             */
/*   Updated: 2025/03/26 14:51:34 by cbouhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	ft_pwd(void)
{
	int		i;
	char	path[1024];

	if (!getcwd(path, sizeof(path)))
	{
		printf("error get path %p\n", path);
		return ;
	}
	i = 0;
	while (path[i])
	{
		write(1, &path[i], 1);
		i++;
	}
	write(1, "\n", 1);
}

/* Check for change sizeof buffer*/
// maybe change this error output.