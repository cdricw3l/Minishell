/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_bit_32.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cw3l <cw3l@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 18:50:44 by cw3l              #+#    #+#             */
/*   Updated: 2024/12/13 10:05:19 by cw3l             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_bit_16(int n)
{
	int		bit;
	char	c;

	bit = 31;
	while (bit >= 0)
	{
		c = ((n >> bit) & 1) + '0';
		write(1, &c, 1);
		bit--;
	}
	write(1, "\n", 1);
}
