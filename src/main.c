/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaker <ohaker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 17:51:40 by ohaker            #+#    #+#             */
/*   Updated: 2025/05/12 02:04:08 by ohaker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	read_map(char *file, t_map *map)
{
	int	fd;

	fd = height_reopen(file, map);
	if (!alloc_z_matrix(map))
	{
		// free(map->z_matrix);
		return ;
	}
	process_lines(fd, map);
	close(fd);
}

void	draw_segment(t_data *data, t_map *map, t_point *p1, t_point *p2)
{
	get_color(map, p1->z);
	calculate_iso(map, p1);
	calculate_iso(map, p2);
	draw_line(data, p1, p2, map->color);
}

void	draw_map(t_data *data, t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (!map->z_matrix[y])
				return ;
			draw_point_links(data, map, x, y);
			x++;
		}
		y++;
	}
}

int	main(int argc, char **argv)
{
	t_map	map;
	t_data	data;

	if (argc != 2)
	{
		ft_printf("Usage: ./fdf <filename>\n");
		return (1);
	}
	read_map(argv[1], &map);
	if (!map.z_matrix)
	{
		ft_printf("Error: Failed to read map\n");
		return (1);
	}
	map.scale = WIN_WIDTH / (map.width * 2);
	map.z_scale = (map.scale / 3) * 2;
	init_data(&data, &map);
	draw_map(&data, &map);
	mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
	mlx_hook(data.win, 2, 1L << 0, handle_key, &data);
	mlx_hook(data.win, 17, 0, handle_destroy, &data);
	mlx_loop(data.mlx);
	cleanup_and_exit(&data);
	return (0);
}
