/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaker <ohaker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:23:56 by ohaker            #+#    #+#             */
/*   Updated: 2025/05/12 17:53:14 by ohaker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	calculate_iso(t_map *map, t_point *point)
{
	float	sx;
	float	sy;
	t_iso	iso;

	sx = point->x * map->scale;
	sy = point->y * map->scale;
	iso.angle = 0.523599f;
	iso.centered_x = sx - (map->width - 1) * map->scale / 2;
	iso.centered_y = sy - (map->height - 1) * map->scale / 2;
	iso.projected_x = (iso.centered_x - iso.centered_y) * cos(iso.angle);
	iso.projected_y = (iso.centered_x + iso.centered_y) * sin(iso.angle)
		- (point->z * map->z_scale);
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
