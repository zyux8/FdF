/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaker <ohaker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 21:19:04 by ohaker            #+#    #+#             */
/*   Updated: 2025/05/24 00:36:02 by ohaker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

int	handle_destroy(t_data *data)
{
	cleanup_and_exit(data);
	return (0);
}

int	handle_zoom(int keycode, t_data *data)
{
	if (keycode == KEY_J)
		data->map->scale += 1;
	else if (keycode == KEY_K && (data->map->scale > 1))
		data->map->scale -= 1;
	redraw_map(data);
	return (0);
}

int	handle_z(int keycode, t_data *data)
{
	if (keycode == KEY_I)
		data->map->z_scale += 0.2;
	else if (keycode == KEY_O && (data->map->z_scale > 0))
		data->map->z_scale /= 2;
	redraw_map(data);
	return (0);
}

int	handle_offset(int keycode, t_data *data)
{
	if (keycode == KEY_UP && (data->map->offset_y > -(WIN_HEIGHT / 2)))
		data->map->offset_y -= 10;
	else if (keycode == KEY_DOWN && (data->map->offset_y < (WIN_HEIGHT / 2)))
		data->map->offset_y += 10;
	else if (keycode == KEY_RIGHT && (data->map->offset_x < (WIN_WIDTH / 2)))
		data->map->offset_x += 10;
	else if (keycode == KEY_LEFT && (data->map->offset_x > -(WIN_WIDTH / 2)))
		data->map->offset_x -= 10;
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
	else if (keycode == KEY_UP || keycode == KEY_DOWN || keycode == KEY_RIGHT
		|| keycode == KEY_LEFT)
		handle_offset(keycode, data);
	return (0);
}
