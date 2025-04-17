/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_print.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouhadr <cbouhadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 14:16:19 by cbouhadr          #+#    #+#             */
/*   Updated: 2025/04/17 15:21:28 by cbouhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_split_print(char **split)
{
	int i;

	i = 0;
	while (split[i])
	{
		write(1, split[i], ft_strlen(split[i]));
		write(1, "\n", 1);
		i++;
	}
}
