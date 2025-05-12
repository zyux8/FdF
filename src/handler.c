/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaker <ohaker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 21:19:04 by ohaker            #+#    #+#             */
/*   Updated: 2025/05/12 18:50:24 by ohaker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

int	handle_destroy(t_data *data)
{
	// mlx_destroy_image(data->mlx, data->img);
	// mlx_destroy_window(data->mlx, data->win);
	// mlx_destroy_display(data->mlx);
	// free(data->mlx);
	// exit(0);
	cleanup_and_exit(data);
	return (0);
}

int	handle_zoom(int keycode, t_data *data)
{
	if (keycode == KEY_J)
		data->map->scale += 1;
	else if (keycode == KEY_K)
	{
		if (data->map->scale > 1)
			data->map->scale -= 1;
	}
	redraw_map(data);
	return (0);
}

int	handle_z(int keycode, t_data *data)
{
	if (keycode == KEY_I)
		data->map->z_scale += 1;
	else if (keycode == KEY_O)
	{
		if (data->map->z_scale > 1)
			data->map->z_scale -= 1;
	}
	redraw_map(data);
	return (0);
}

int	handle_key(int keycode, t_data *data)
{
	if (keycode == KEY_ESC)
		cleanup_and_exit(data);
	else if (keycode == KEY_J || keycode == KEY_K)
		handle_zoom(keycode, data);
	else if (keycode == KEY_I || keycode == KEY_O)
		handle_z(keycode, data);
	return (0);
}
