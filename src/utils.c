/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaker <ohaker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 13:59:56 by ohaker            #+#    #+#             */
/*   Updated: 2025/04/29 18:36:04 by ohaker           ###   ########.fr       */
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

int get_width(char *line)
{
	char **split = ft_split(line, ' ');
	int width = 0;

	while (split[width])
		width++;

	ft_free_split(split);
	return width;
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

void draw_line(t_data *data, int start_x, int start_y, int end_x, int end_y, int color)
{
	int diffx;
	int diffy;
	int err;
	int e2;
	int step_x;
	int step_y;

	diffx = ft_conv_to_pos(end_x - start_x);
	diffy = ft_conv_to_pos(end_y - start_y);
	if (end_x < start_x)
		step_x = -1;
	else
		step_x = 1;
	if (end_y < start_y)
		step_y = -1;
	else
		step_y = 1;
	err = diffx - diffy;
	while (1)
	{
		if (start_x >= 0 && start_y >= 0 && start_x < WIN_WIDTH && start_y < WIN_HEIGHT)
			my_pixel_put(data, start_x, start_y, color);
		if (start_x == end_x && start_y == end_y)
		break ;
		e2 = err * 2;
		if (e2 > -diffy)
		{
			err -= diffy;
			start_x += step_x;
		}
		if (e2 < diffx)
		{
			err += diffx;
			start_y += step_y;
		}
	}
}

void calculate_iso(t_map *map, int x, int y, int z, int *iso_x, int *iso_y)
{
	float center_x;
	float center_y;
	float angle;
	
	center_x = x * SCALE;
	center_y = y * SCALE;
	angle = 0.523599; // 30 degrees in radians (30 * PI / 180)
	*iso_x = (center_x - center_y) * cos(angle);
	*iso_y = (center_x + center_y) * sin(angle) - (z * Z_SCALE);
	*iso_x += map->offset_x;
	*iso_y += map->offset_y;
}

void	free_z_matrix(int **z_matrix, int rows)
{
	int i = 0;
	while (i < rows)
	{
		free(z_matrix[i]);
		i++;
	}
	free(z_matrix);
}
