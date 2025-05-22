/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbry.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaker <ohaker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 16:12:49 by ohaker            #+#    #+#             */
/*   Updated: 2024/11/28 20:07:07 by ohaker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbry(int n, int y)
{
	int	c;

	if (n == -2147483648)
	{
		ft_putstr("-2147483648");
		y += 11;
	}
	else
	{
		if (n < 0)
		{
			ft_putchar('-');
			y++;
			n = -n;
		}
		if (n >= 10)
			y = ft_putnbry(n / 10, y);
		c = (n % 10) + '0';
		ft_putchar(c);
		y++;
	}
	return (y);
}

// int	main(void)
// {
// 	printf("return (of ft_putnbry: %i\n", ft_putnbry(50, 0)));
// 	printf("return (of ft_putnbry: %i\n", ft_putnbry(0, 0)));
// 	printf("return (of ft_putnbry: %i\n", ft_putnbry(-2147483648, 0)));
// 	printf("return (of ft_putnbry: %i\n", ft_putnbry(-50, 0)));
// 	printf("return (of ft_putnbry: %i\n", ft_putnbry(2147483647, 0)));
// }