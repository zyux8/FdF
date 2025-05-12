/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstry.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaker <ohaker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 16:06:23 by ohaker            #+#    #+#             */
/*   Updated: 2024/11/29 18:44:36 by ohaker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstry(char *str, int y)
{
	int	x;

	x = 0;
	if (str == NULL)
	{
		ft_putstr("(null)");
		return (y += 6);
	}
	while (str[x])
	{
		ft_putchar(str[x]);
		x++;
	}
	return (y += x);
}

// int main ()
// {
// 	char *str = "string is 28 characters long";

// 	printf("%i", ft_putstry(str, 0));
// }