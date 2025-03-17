/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_index_of.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouhadr <cbouhadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 12:14:07 by cbouhadr          #+#    #+#             */
/*   Updated: 2024/12/13 12:23:02 by cbouhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <assert.h>

int	ft_index_of(int *arr, int len, int n)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (arr[i] == n)
			return (i);
		i++;
	}
	return (-1);
}
