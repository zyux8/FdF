/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaker <ohaker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:46:15 by ohaker            #+#    #+#             */
/*   Updated: 2024/11/29 15:33:00 by ohaker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_ptr(unsigned long ptr, int y)
{
	int		x;
	char	buffer[16];
	char	*hex_char;

	hex_char = "0123456789abcdef";
	if (ptr == 0)
	{
		ft_putstr("(nil)");
		return (5);
	}
	x = 15;
	while (ptr > 0)
	{
		buffer[x--] = hex_char[ptr % 16];
		ptr /= 16;
	}
	x++;
	ft_putstr("0x");
	y = 2;
	while (x < 16)
	{
		ft_putchar(buffer[x++]);
		y++;
	}
	return (y);
}

// int	main(void)
// {
// 	char *ptr;

// 	printf("%i\n", ft_print_ptr(*ptr, 0));
// 	printf("%i\n", printf("%p\n", ptr));
// }

// int	main(void)
// {
// 	int *ptr = (int *)-ULONG_MAX;
// 	printf("%i\n", ft_print_ptr(-ULONG_MAX, 0));
// 	printf("%i\n", printf("%p", (void *)ptr));
// 	return (0);
// }