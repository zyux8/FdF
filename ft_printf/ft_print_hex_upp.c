/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex_upp.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaker <ohaker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 19:44:07 by ohaker            #+#    #+#             */
/*   Updated: 2024/11/29 18:43:22 by ohaker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_hex_upp(unsigned int ptr, int y)
{
	int		x;
	char	buffer[16];
	char	*hex_char;

	hex_char = "0123456789ABCDEF";
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

// int	main(void)
// {
// 	printf("%lu\n", LONG_MAX);
// 	printf("%lu\n", LONG_MIN);
// 	printf("%lu\n\n", ULONG_MAX);
// 	printf("%i\n", ft_print_hex_upp(LONG_MAX, 0));
// 	printf("%i\n", ft_print_hex_upp(LONG_MIN, 0));
// 	printf("%i\n", ft_print_hex_upp(ULONG_MAX, 0));
// 	printf("%i\n", ft_print_hex_upp(9223372036854775807LL, 0));
// }
