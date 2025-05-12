/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunsignbr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaker <ohaker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 19:51:31 by ohaker            #+#    #+#             */
/*   Updated: 2024/11/29 15:37:44 by ohaker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putunsignbr(unsigned int n, int y)
{
	int		x;
	char	buffer[10];

	x = 0;
	if (n == 0)
	{
		ft_putchar('0');
		return (++y);
	}
	while (n > 0)
	{
		buffer[x++] = (n % 10) + '0';
		n /= 10;
	}
	while (x > 0)
	{
		ft_putchar(buffer[--x]);
		y++;
	}
	return (y);
}

// int	main(void)
// {
// 	int nbr = 5402;

// 	printf("%i\n", ft_putunsignbr(nbr, 0));
// }