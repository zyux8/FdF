/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaker <ohaker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 17:51:40 by ohaker            #+#    #+#             */
/*   Updated: 2025/04/26 21:29:42 by ohaker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"
#include "../libft/libft.h"

int get_width(char *line)
{
	int width;
	int x;

	width = 0;
	x = 0;
	while (line[x])
	{
		if (line[x] == ' ')
			width++;
		x++;
	}
	return (width + 1);
}

void	read_map(int fd, t_map *map)
{
	char **split;
	char *line;
	int x;
	int y;

	x = 0;
	y = 0;
	fd = open("test.fdf", O_RDONLY);
	map->height = ft_count_lines(fd);
	close(fd);
	map->z_matrix = malloc(sizeof(int *) * map->height);
	fd = open("test.fdf", O_RDONLY);
	while ((line = get_next_line(fd)))
	{
		y = 0;
		if (x == 0)
			map->width = get_width(line);
		map->z_matrix[x] = malloc(sizeof(int) * map->width);
		split = ft_split(line, ' ');
		while (y < map->width)
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

// int main(void)
// {
//     t_map map;
//     int fd;

//     fd = open("test.fdf", O_RDONLY);
//     if (fd < 0)
//         return (1);
//     read_map(fd, &map);

//     close(fd);
//     return (0);
// }

// int main(void)
// {
//     t_map map;
//     int fd;

//     fd = open("test.fdf", O_RDONLY);
//     if (fd < 0)
//     {
//         perror("Error opening file");
//         return (1);
//     }

//     read_map(fd, &map);  // This fills map.z_matrix, map.width, map.height
//     close(fd);

//     // Test: print the z_matrix
//     for (int i = 0; i < map.height; i++)
//     {
//         for (int j = 0; j < map.width; j++)
//         {
//             printf("%d ", map.z_matrix[i][j]);
//         }
//         printf("\n");
//     }

//     return (0);
// }

int main(void)
{
    // t_map map;
	t_data data;
    // int fd;

    // fd = open("test.fdf", O_RDONLY);
    // if (fd < 0)
    // {
    //     perror("Error opening file");
    //     return (1);
    // }
    // read_map(fd, &map);  // This fills map.z_matrix, map.width, map.height
    // close(fd);
	t_vars vars;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 1000, 800, "FdF");
	data.img = mlx_new_image(vars.mlx, 1000, 800);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);

	// draw_map(&vars, &map); // where you draw all lines
	draw_line(&data, 100, 100, 400, 400, 0x00FF0000);
	draw_line(&data, 400, 400, 600, 100, 0x00FF0000);
	// my_pixel_put(&data, 200, 200, 0x00FF0000);

	mlx_put_image_to_window(vars.mlx, vars.win, data.img, 0, 0);
	mlx_loop(vars.mlx); // keeps window open

	return (0);
}