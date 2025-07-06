/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaker <ohaker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:23:56 by ohaker            #+#    #+#             */
/*   Updated: 2025/05/24 00:02:48 by ohaker           ###   ########.fr       */
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
	point->iso_x = (int)iso.projected_x + WIN_WIDTH / 2 + map->offset_x;
	point->iso_y = (int)iso.projected_y + WIN_HEIGHT / 2 + map->offset_y;
}

unsigned int	hsv_to_rgb(float h, float s, float v)
{
	float	c = v * s;
	float	x = c * (1 - fabsf(fmodf(h / 60.0f, 2) - 1));
	float	m = v - c;
	float	r, g, b;

	if (h < 60) { r = c; g = x; b = 0; }
	else if (h < 120) { r = x; g = c; b = 0; }
	else if (h < 180) { r = 0; g = c; b = x; }
	else if (h < 240) { r = 0; g = x; b = c; }
	else if (h < 300) { r = x; g = 0; b = c; }
	else { r = c; g = 0; b = x; }

	unsigned int ir = (unsigned int)((r + m) * 255.0f);
	unsigned int ig = (unsigned int)((g + m) * 255.0f);
	unsigned int ib = (unsigned int)((b + m) * 255.0f);
	return (ir << 16) | (ig << 8) | ib;
}

// Main color mapping
void	get_color(t_map *map, int z)
{
	float	hue;

	if (z < 0)
		hue = 240 + (z * -1 > 255 ? 255 : -z); // Negative z -> blue to purple
	else if (z > 255)
		hue = 0; // Cap max
	else
		hue = 240.0f - ((float)z / 255.0f) * 240.0f; // Map 0–255 to 240–0 (blue to red)

	map->color = hsv_to_rgb(hue, 1.0f, 1.0f);
}
