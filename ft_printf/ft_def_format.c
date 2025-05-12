/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_def_format.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaker <ohaker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 21:05:23 by ohaker            #+#    #+#             */
/*   Updated: 2024/11/29 18:45:00 by ohaker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *str)
{
	size_t	x;

	x = 0;
	while (str[x])
	{
		ft_putchar(str[x]);
		x++;
	}
}

int	ft_def_format(const char format, va_list args, int y)
{
	if (format == 'c')
	{
		ft_putchar(va_arg(args, int));
		y = 1;
	}
	else if (format == 's')
		y = ft_putstry(va_arg(args, char *), y);
	else if (format == 'p')
		y = ft_print_ptr(va_arg(args, unsigned long), y);
	else if (format == 'd' || format == 'i')
		y = ft_putnbry(va_arg(args, int), y);
	else if (format == 'u')
		y = ft_putunsignbr(va_arg(args, unsigned int), y);
	else if (format == 'x')
		y = ft_print_hex(va_arg(args, unsigned long), y);
	else if (format == 'X')
		y = ft_print_hex_upp(va_arg(args, long), y);
	else if (format == '%')
	{
		ft_putchar('%');
		y = 1;
	}
	return (y);
}

/* Argument Type								Second Parameter for va_arg
int, short, char								int
unsigned int, unsigned short, unsigned char		unsigned int
long											long
unsigned long									unsigned long
float, double									double
char * (strings)								char *
void *											void * */