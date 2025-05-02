/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaker <ohaker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 17:51:40 by ohaker            #+#    #+#             */
/*   Updated: 2025/05/02 20:16:50 by ohaker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void read_map(int fd, t_map *map)
{
    char **split;
    char *line;
    int x;
    int y;
    int current_width;

	x = 0;
    map->height = ft_count_lines(fd);
    lseek(fd, 0, SEEK_SET);
	// close(fd);
	// fd = open("test.fdf", O_RDONLY);
    map->z_matrix = malloc(sizeof(int *) * map->height);
    if (!map->z_matrix)
    {
		printf("Error allocating memory for z_matrix\n");
		free_z_matrix(map->z_matrix, x);
		map->z_matrix = NULL;
        return;
    }
    while ((line = get_next_line(fd)))
    {
		split = ft_split(line, ' ');
		if (!split)
        {
			printf("Error: ft_split failed\n");
            free(line);
            free_z_matrix(map->z_matrix, x);
            map->z_matrix = NULL;
            return;
        }
        current_width = 0;
        while (split[current_width])
            current_width++;
		if (x == 0)
			map->width = current_width;
        else if (current_width != map->width)
		{
			printf("Error: Inconsistent line width at line %d (expected %d, got %d)\n", x, map->width, current_width);
			free(line);
			ft_free_split(split);
			free_z_matrix(map->z_matrix, x);
			return;
		}        
		map->z_matrix[x] = malloc(sizeof(int) * current_width);
        if (!map->z_matrix[x])
        {
            printf("Error allocating memory for row %d\n", x);
            return;
        }
        y = 0;
        while (y < current_width)
        {
            map->z_matrix[x][y] = ft_atoi(split[y]);
            y++;
        }
        ft_free_split(split);
        free(line);
        x++;
    }
	close(fd);
}

void draw_map(t_data *data,  t_map *map)
{
	int	x;
	int	y;
	t_point p1;
	t_point p2;

	y = 0;
	printf("width: %d\n", map->width);
	printf("height: %d\n", map->height);
	while(y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (y >= map->height || x >= map->width || !map->z_matrix[y])
				return;
            if (x < map->width - 1)
            {
				p1 = (t_point){x, y, map->z_matrix[y][x], 0, 0};
				p2 = (t_point){x + 1, y, map->z_matrix[y][x + 1], 0, 0};
				get_color(map, map->z_matrix[y][x]);
                calculate_iso(map, &p1);
                calculate_iso(map, &p2);
                draw_line(data, &p1, &p2, map->color);
            }
            if (y < map->height - 1)
			{
				p1 = (t_point){x, y, map->z_matrix[y][x], 0, 0};
				p2 = (t_point){x, y + 1, map->z_matrix[y + 1][x], 0, 0};
				get_color(map, map->z_matrix[y][x]);
                calculate_iso(map, &p1);
                calculate_iso(map, &p2);
                draw_line(data, &p1, &p2, map->color);
            }
			x++;
		}
		y++;
	}
}

int main(int argc, char **argv)
{
    t_map map;
	t_data data;
	t_vars vars;
    int fd;

	if (argc != 2)
	{
		printf("Usage: ./fdf <filename>\n");
		return (1);
	}
	fd = open(argv[1], O_RDONLY);
	// if (fd < 0)
	// {
	// 	perror("Error opening file");
	// 	return (1);
	// }
	
	read_map(fd, &map);
	if (!map.z_matrix)
	{
		printf("Error: Failed to read map\n");
		return (1);
	}
	close(fd);
	
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, WIN_WIDTH, WIN_HEIGHT, "FdF");
	data.img = mlx_new_image(vars.mlx, WIN_WIDTH, WIN_HEIGHT);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);
 
	// for (int i = 0; i < map.height; i++)
	// {
	// 	for (int j = 0; j < map.width; j++)
	// 	{
	// 		printf("%d ", map.z_matrix[i][j]);
	// 	}
	// 	printf("\n");
	// }
	
	printf("map print\n");
	draw_map(&data, &map); // where you draw all lines
	// draw_line(&data, 100, 100, 250, 400, 0x00FFFFFF);
	// draw_line(&data, 250, 400, 500, 120, 0x00FF0000);
	// draw_line(&data, 500, 120, 100, 100, 0x0000FF00);
	
	// my_pixel_put(&data, 100, 100, 0x00FF0000);
	// my_pixel_put(&data, 101, 101, 0x0000FF00);
	// my_pixel_put(&data, 102, 102, 0x000000FF);
	// my_pixel_put(&data, 103, 103, 0x00FFFF00);
	// my_pixel_put(&data, 104, 104, 0x00FF00FF);

	mlx_put_image_to_window(vars.mlx, vars.win, data.img, 0, 0);
	mlx_loop(vars.mlx); // keeps window open

	return (0);
}
