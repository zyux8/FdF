/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaker <ohaker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 17:51:26 by ohaker            #+#    #+#             */
/*   Updated: 2025/05/12 17:52:43 by ohaker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	redraw_map(t_data *data)
{
	mlx_destroy_image(data->mlx, data->img);
	data->img = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGHT);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
			&data->line_length, &data->endian);
	draw_map(data, data->map);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}

void	draw_point_links(t_data *data, t_map *map, int x, int y)
{
	t_point	p1;
	t_point	p2;

	p1 = (t_point){x, y, map->z_matrix[y][x], 0, 0};
	if (x < map->width - 1)
	{
		p2 = (t_point){x + 1, y, map->z_matrix[y][x + 1], 0, 0};
		draw_segment(data, map, &p1, &p2);
	}
	if (y < map->height - 1)
	{
		p2 = (t_point){x, y + 1, map->z_matrix[y + 1][x], 0, 0};
		draw_segment(data, map, &p1, &p2);
	}
}

void	draw_segment(t_data *data, t_map *map, t_point *p1, t_point *p2)
{
	get_color(map, p1->z);
	calculate_iso(map, p1);
	calculate_iso(map, p2);
	draw_line(data, p1, p2, map->color);
}

void	draw_line(t_data *data, t_point *p1, t_point *p2, int color)
{
	t_draw	draw;

	draw.diffx = ft_conv_to_pos(p2->iso_x - p1->iso_x);
	draw.diffy = ft_conv_to_pos(p2->iso_y - p1->iso_y);
	if (p2->iso_x < p1->iso_x)
		draw.step_x = -1;
	else
		draw.step_x = 1;
	if (p2->iso_y < p1->iso_y)
		draw.step_y = -1;
	else
		draw.step_y = 1;
	draw.err = draw.diffx - draw.diffy;
	while (1)
	{
		if (p1->iso_x >= 0 && p1->iso_y >= 0 && p1->iso_x < WIN_WIDTH
			&& p1->iso_y < WIN_HEIGHT)
			my_pixel_put(data, p1->iso_x, p1->iso_y, color);
		if (p1->iso_x == p2->iso_x && p1->iso_y == p2->iso_y)
			break ;
		draw.e2 = draw.err * 2;
		update_line_drawing(&draw, p1);
	}
}
