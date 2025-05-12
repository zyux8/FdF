/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaker <ohaker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 18:01:06 by ohaker            #+#    #+#             */
/*   Updated: 2025/05/09 19:13:37 by ohaker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	// int		x;
	int		y;
	va_list	args;

	// x = 0;
	y = 0;
	va_start(args, format);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			y += ft_def_format(*format, args, 0);
		}
		else
		{
			ft_putchar(*format);
			y++;
		}
		format++;
	}
	va_end(args);
	return (y);
}

// int	main(void)
// {
// 	printf(" %x ", LONG_MAX);
// ft_printf(" %x ", LONG_MAX);
// int *ptr = (int *)LONG_MIN;
// 	int *ptr1 = (int *)LONG_MAX;
// 	printf("%i\n", ft_printf(" %p %p ", ptr, ptr1));
// 	printf("%i\n", printf(" %p %p ", ptr, ptr1));
// }

// int	main(void)
// {
// 	char			*str;
// 	int				nbr;
// 	void			*ptr;
// 	unsigned int	unbr;

// 	ptr = "points here";
// 	unbr = 44442222;
// 	str = "STRING";
// 	nbr = 2345647;
// 	ft_printf("Own:\nString: %s\nPointer: %p\nInt: %d\nUnsigned:
// 		%u\nHex low:%x\nHex upp:%X\nPercent: %%\nUndef: %g\n", str, &ptr, nbr,
// 		unbr, nbr,
// 			nbr);
// 	printf("\n\nC:\nString: %s\nPointer: %p\nInt: %d\nUnsigned:
// 		%u\nHex low:%x\nHex upp:%X\nPercent: %%\nUndef: \n\n\n", str, &ptr, nbr,
// 		unbr, nbr,
// 			nbr);
// 	ft_printf("Own: %i\n", ft_printf("%d characters\n", nbr));
// 	printf("C: %i\n", printf("%i characters\n", nbr));
// 	return (0);
// }

// // int main(void)
// // {
// 	printf("%i", ft_printf("das ist ein %i", 50));
// 	return (0);
// }

// void	rehkampf(char *mo, char *reh)
// {
// 	int		gender;
// 	void	aufmerksam;
// 	int		geweih;

// 	if (reh[aufmerksamkeit] == false)
// 		return (sieg_mo);
// 	else
// 	{
// 		if (reh[gender] == weiblich)
// 			return (sieg_mo);
// 		else if (reh[gender] == maennlich)
// 		{
// 			if (reh[geweih] == true)
// 				return (sieg_reh);
// 			else
// 				return (sieg_mo);
// 		}
// 	}
// }