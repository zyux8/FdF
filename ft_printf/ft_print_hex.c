/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaker <ohaker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 18:01:32 by ohaker            #+#    #+#             */
/*   Updated: 2024/11/29 18:44:15 by ohaker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_hex(unsigned int ptr, int y)
{
	int		x;
	char	buffer[16];
	char	*hex_char;

	hex_char = "0123456789abcdef";
	if (ptr == 0)
	{
		ft_putchar('0');
		return (y + 1);
	}
	x = 0;
	while (ptr > 0)
	{
		buffer[x++] = hex_char[ptr % 16];
		ptr /= 16;
	}
	y += x;
	while (x > 0)
		ft_putchar(buffer[--x]);
	return (y);
}
