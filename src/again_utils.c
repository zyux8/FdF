/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   again_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaker <ohaker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 23:41:16 by ohaker            #+#    #+#             */
/*   Updated: 2025/05/12 02:00:50 by ohaker           ###   ########.fr       */
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

void	cleanup_and_exit(t_data *data)
{
	if (data->map->z_matrix)
		free_z_matrix(data->map->z_matrix, data->map->height);
	if (data->img)
		mlx_destroy_image(data->mlx, data->img);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	exit(0);
}

void	init_data(t_data *data, t_map *map)
{
	map->scale = WIN_WIDTH / (map->width * 2);
	map->z_scale = (map->scale / 3) * 2;
	data->map = map;
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, WIN_WIDTH, WIN_HEIGHT, "FdF");
	data->img = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGHT);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
			&data->line_length, &data->endian);
}
