/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaker <ohaker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 17:51:40 by ohaker            #+#    #+#             */
/*   Updated: 2025/05/04 21:21:37 by ohaker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	read_map(char *file, t_map *map)
{
	char	*line;
	int		x;
	int		fd;

	x = 0;
	fd = height_reopen(file, map);
	map->z_matrix = malloc(sizeof(int *) * map->height);
	if (!map->z_matrix)
	{
		handle_read_error(map, NULL, NULL, 0,
			"Error allocating memory for z_matrix");
	}
	while ((line = get_next_line(fd)))
	{
		if (!process_line(line, map, x))
		{
			handle_read_error(map, line, NULL, x, "Error processing line");
			return ;
		}
		free(line);
		x++;
	}
	close(fd);
}

void	draw_segment(t_data *data, t_map *map, int x1, int y1, int x2, int y2)
{
	t_point	p1;
	t_point	p2;

	p1 = (t_point){x1, y1, map->z_matrix[y1][x1], 0, 0};
	p2 = (t_point){x2, y2, map->z_matrix[y2][x2], 0, 0};
	get_color(map, p1.z);
	calculate_iso(map, &p1);
	calculate_iso(map, &p2);
	draw_line(data, &p1, &p2, map->color);
}

void	draw_map(t_data *data, t_map *map)
{
	int	x;
	int	y;

	y = 0;
	printf("width: %d\n", map->width);
	printf("height: %d\n", map->height);
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (y >= map->height || x >= map->width || !map->z_matrix[y])
				return ;
			if (x < map->width - 1)
				draw_segment(data, map, x, y, x + 1, y);
			if (y < map->height - 1)
				draw_segment(data, map, x, y, x, y + 1);
			x++;
		}
		y++;
	}
}

int	main(int argc, char **argv)
{
	t_map	map;
	t_data	data;
	t_vars	vars;
	int		fd;

	if (argc != 2)
	{
		printf("Usage: ./fdf <filename>\n");
		return (1);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		return (1);
	}
	read_map(argv[1], &map);
	if (!map.z_matrix)
	{
		printf("Error: Failed to read map\n");
		return (1);
	}
	close(fd);
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, WIN_WIDTH, WIN_HEIGHT, "FdF");
	data.img = mlx_new_image(vars.mlx, WIN_WIDTH, WIN_HEIGHT);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel,
			&data.line_length, &data.endian);
	draw_map(&data, &map);
	mlx_put_image_to_window(vars.mlx, vars.win, data.img, 0, 0);
	mlx_hook(vars.win, 2, 1L << 0, handle_keypress, &data);         // Key press
	mlx_hook(vars.win, 17, 0, handle_destroy, &data);               // Window close (X)
	mlx_loop(vars.mlx);
	return (0);
}
