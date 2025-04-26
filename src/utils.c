/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaker <ohaker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 13:59:56 by ohaker            #+#    #+#             */
/*   Updated: 2025/04/26 22:07:57 by ohaker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void my_pixel_put(t_data *data, int x, int y, int color)
{
	char *dst;
	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int ft_count_lines(int fd)
{
	int count = 0;
	char *line;

	while ((line = get_next_line(fd)) != NULL)
	{
		count++;
		free(line);
	}
	return count;
}

// void draw_line(t_data *data, int xS, int yS, int xE, int yE, int color)
// {
// 	int diffx;
// 	int diffy;
// 	int err;
	
	
// 	diffx = xE - xS;
// 	diffy = yE - yS;
// }

void draw_line(t_data *data, int xS, int yS, int xE, int yE, int color)
{
	int diffx;
	int diffy;
	int err;
	int sx;
	int sy;

	diffx = ft_conv_to_pos(xE - xS);
	diffy = ft_conv_to_neg(yE - yS);
	if (xE < xS)
		sx = -1;
	else
		sx = 1;
	if (yE < yS)
		sy = -1;
	else
		sy = 1;
	err = diffx / 2;
	while (xS != xE && yS != yE)
	{
		if (xS >= 0 && yS >= 0 && xS < WIN_WIDTH && yS < WIN_HEIGHT)
			my_pixel_put(data, xS, yS, color);
		err *= 2;
		if (err >= diffy)
		{
			err = (err / 2) + diffy;
			xS += sx;
		}
		if (err <= diffx)
		{
			err = (err / 2) +diffx;
			yS += sy;
		}
	}
}
