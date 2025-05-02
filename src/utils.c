/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaker <ohaker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 13:59:56 by ohaker            #+#    #+#             */
/*   Updated: 2025/05/02 20:08:26 by ohaker           ###   ########.fr       */
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

int	get_width(char *line)
{
	char	**split;
	int		width;

	split = ft_split(line, ' ');
	width = 0;
	while (split[width])
		width++;
	ft_free_split(split);
	return (width);
}

int	ft_count_lines(int fd)
{
	int		count;
	char	*line;

	count = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		count++;
		free(line);
	}
	return (count);
}

void	draw_line(t_data *data, t_point *p1, t_point *p2, int color)
{
	int		err;
	int		e2;
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
	err = draw.diffx - draw.diffy;
	while (1)
	{
		if (p1->iso_x >= 0 && p1->iso_y >= 0 && p1->iso_x < WIN_WIDTH
			&& p1->iso_y < WIN_HEIGHT)
			my_pixel_put(data, p1->iso_x, p1->iso_y, color);
		if (p1->iso_x == p2->iso_x && p1->iso_y == p2->iso_y)
			break ;
		e2 = err * 2;
		if (e2 > -draw.diffy)
		{
			err -= draw.diffy;
			p1->iso_x += draw.step_x;
		}
		if (e2 < draw.diffx)
		{
			err += draw.diffx;
			p1->iso_y += draw.step_y;
		}
	}
}

void	calculate_iso(t_map *map, t_point *point)
{
	float	sx;
	float	sy;
	t_iso	iso;

	sx = point->x * SCALE;
	sy = point->y * SCALE;
	iso.angle = 0.523599f;
	iso.centered_x = sx - (map->width - 1) * SCALE / 2;
	iso.centered_y = sy - (map->height - 1) * SCALE / 2;
	iso.projected_x = (iso.centered_x - iso.centered_y) * cos(iso.angle);
	iso.projected_y = (iso.centered_x + iso.centered_y) * sin(iso.angle)
		- (point->z * Z_SCALE) + 100;
	point->iso_x = (int)iso.projected_x + WIN_WIDTH / 2;
	point->iso_y = (int)iso.projected_y + WIN_HEIGHT / 2;
}

void	get_color(t_map *map, int z)
{
	if (z > 20)
		map->color = 0x00FFAAFF;
	else if (z > 15)
		map->color = 0x00FF00FF;
	else if (z > 10)
		map->color = 0x00FF0000;
	else if (z > 5)
		map->color = 0x00FFA500;
	else if (z > 0)
		map->color = 0x00FFFF00;
	else if (z == 0)
		map->color = 0x00FFFFFF;
	else
		map->color = 0x000000FF;
}

void	free_z_matrix(int **z_matrix, int rows)
{
	int	i;

	i = 0;
	while (i < rows)
	{
		free(z_matrix[i]);
		i++;
	}
	free(z_matrix);
}
