/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaker <ohaker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 17:51:40 by ohaker            #+#    #+#             */
/*   Updated: 2025/05/22 22:30:26 by ohaker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

int	read_map(char *file, t_map *map)
{
	int	fd;

	fd = height_reopen(file, map);
	if (fd < 0)
		return (1);
	if (!alloc_z_matrix(map))
		return (1);
	process_lines(fd, map);
	close(fd);
	return (0);
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

void	init_data(t_data *data, t_map *map)
{
	map->scale = WIN_WIDTH / (map->width * 2);
	map->z_scale = (map->scale / 3) * 2;
	if (map->z_scale > 20)
		map->z_scale = 20;
	else if (map->z_scale < 1)
		map->z_scale = 1;
	map->offset_x = 0;
	map->offset_y = 0;
	data->map = map;
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, WIN_WIDTH, WIN_HEIGHT, "FdF");
	data->img = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGHT);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
			&data->line_length, &data->endian);
}

void	process_lines(int fd, t_map *map)
{
	char	*line;
	int		x;

	x = 0;
	line = get_next_line(fd);
	if (!line)
	{
		handle_read_error(map, line, NULL, x);
		ft_printf("Error reading line\n");
		return ;
	}
	while (line)
	{
		if (!process_z_value(line, map, x))
		{
			handle_read_error(map, line, NULL, x);
			ft_printf("Error processing line\n");
			return ;
		}
		free(line);
		x++;
		line = get_next_line(fd);
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
	if (read_map(argv[1], &map) || !map.z_matrix)
	{
		ft_printf("Error: Failed to read map\n");
		return (1);
	}
	init_data(&data, &map);
	draw_map(&data, &map);
	mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
	mlx_hook(data.win, 2, 1L << 0, handle_key, &data);
	mlx_hook(data.win, 17, 0, handle_destroy, &data);
	mlx_loop(data.mlx);
	cleanup_and_exit(&data);
	return (0);
}
