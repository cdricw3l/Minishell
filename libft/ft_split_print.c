/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_print.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouhadr <cbouhadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 14:16:19 by cbouhadr          #+#    #+#             */
/*   Updated: 2025/03/28 14:23:39 by cbouhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_split_print(char **split)
{
	while (*split)
	{
		write(1, *split, ft_strlen(*split));
		write(1, "\n", 1);
		split++;
	}
}
