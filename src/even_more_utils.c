/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   even_more_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaker <ohaker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 17:22:45 by ohaker            #+#    #+#             */
/*   Updated: 2025/05/12 01:59:50 by ohaker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

int	alloc_z_matrix(t_map *map)
{
	map->z_matrix = malloc(sizeof(int *) * map->height);
	if (!map->z_matrix)
	{
		handle_read_error(map, NULL, NULL, map->height);
		ft_printf("Error allocating memory for z_matrix");
		return (0);
	}
	return (1);
}

void	process_lines(int fd, t_map *map)
{
	char	*line;
	int		x;

	x = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (!process_z_value(line, map, x))
		{
			handle_read_error(map, line, NULL, x);
			ft_printf("Error processing line");
			return ;
		}
		free(line);
		x++;
		line = get_next_line(fd);
	}
}

void	draw_point_links(t_data *data, t_map *map, int x, int y)
{
	t_point	p1;
	t_point	p2;

	p1 = (t_point){x, y, map->z_matrix[y][x], 0, 0};
	if (x < map->width - 1)
	{
		p2 = (t_point){x + 1, y, map->z_matrix[y][x + 1], 0, 0};
		draw_segment(data, map, &p1, &p2);
	}
	if (y < map->height - 1)
	{
		p2 = (t_point){x, y + 1, map->z_matrix[y + 1][x], 0, 0};
		draw_segment(data, map, &p1, &p2);
	}
}
