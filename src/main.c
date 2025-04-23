/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaker <ohaker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 17:51:40 by ohaker            #+#    #+#             */
/*   Updated: 2025/04/23 21:39:43 by ohaker           ###   ########.fr       */
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
	map->height = ft_count_lines(fd);
	map->z_matrix = malloc(sizeof(int *) * map->height);
	fd = open("test.fdf", O_RDONLY);
	while ((line = get_next_line(fd)))
	{
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

int main(void)
{
    t_map map;
    int fd;

    fd = open("test.fdf", O_RDONLY);
    if (fd < 0)
        return (1);
    read_map(fd, &map);

    close(fd);
    return (0);
}