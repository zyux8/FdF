/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaker <ohaker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 21:19:04 by ohaker            #+#    #+#             */
/*   Updated: 2025/05/07 21:04:07 by ohaker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

// int	handle_keypress(int keycode, t_data *data)
// {
// 	// t_map	*map;

// 	if (keycode == KEY_ESC)
// 	{
// 		mlx_destroy_image(data->mlx, data->img);
// 		mlx_destroy_window(data->mlx, data->win);
// 		mlx_destroy_display(data->mlx);
// 		free(data->mlx);
// 		exit(0);
// 	}
// 	return (0);
// }

int	handle_destroy(t_data *data)
{
	mlx_destroy_image(data->mlx, data->img);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	exit(0);
	return (0);
}

int	handle_key(int keycode, t_data *data)
{
	// t_map	*map;

	// map = &data->map;
	printf("Key pressed: %d\n", keycode);
	printf("Width: %d, Height: %d, Scale: %d, Offset X: %d, Offset Y: %d\n",
		data->map->width, data->map->height, data->map->scale,
		data->map->offset_x, data->map->offset_y);
	if (keycode == KEY_ESC)
	{
		cleanup_and_exit(data);
	}
	else if (keycode == KEY_J)
	{
		data->map->scale += 1;
		redraw_map(data);
	}
	else if (keycode == KEY_K)
	{
		if (data->map->scale > 1)
			data->map->scale -= 1;
		redraw_map(data);
	}
	else if (keycode == KEY_UP)
	{
		printf("UP WE GO\n");
		data->map->offset_y -= 10;
		redraw_map(data);
	}
	else if (keycode == KEY_DOWN)
	{
		data->map->offset_y += 10;
		redraw_map(data);
	}
	else if (keycode == KEY_LEFT)
	{
		data->map->offset_x -= 10;
		redraw_map(data);
	}
	else if (keycode == KEY_RIGHT)
	{
		data->map->offset_x += 10;
		redraw_map(data);
	}
	return (0);
}

void redraw_map(t_data *data)
{
    mlx_clear_window(data->mlx, data->win);
    draw_map(data, data->map);
}

void	cleanup_and_exit(t_data *data)
{
	// if (data->map.z_matrix)
	// 	free_z_matrix(data->map.z_matrix, data->map.height);
	printf("Exiting program...\n");
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
