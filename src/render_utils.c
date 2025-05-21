/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaker <ohaker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 13:59:56 by ohaker            #+#    #+#             */
/*   Updated: 2025/05/12 17:52:39 by ohaker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	my_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	update_line_drawing(t_draw *draw, t_point *p1)
{
	if (draw->e2 > -draw->diffy)
	{
		draw->err -= draw->diffy;
		p1->iso_x += draw->step_x;
	}
	if (draw->e2 < draw->diffx)
	{
		draw->err += draw->diffx;
		p1->iso_y += draw->step_y;
	}
}
