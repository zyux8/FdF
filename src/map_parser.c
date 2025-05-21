/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaker <ohaker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 17:22:45 by ohaker            #+#    #+#             */
/*   Updated: 2025/05/21 17:56:20 by ohaker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

int	ft_count_lines(int fd)
{
	int		count;
	char	*line;

	count = 0;
	line = get_next_line(fd);
	while (line)
	{
		count++;
		free(line);
		line = get_next_line(fd);
	}
	return (count);
}

int	height_reopen(char *file, t_map *map)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("Error opening file: %s\n", file);
		return (0);
	}
	map->height = ft_count_lines(fd);
	close(fd);
	fd = open(file, O_RDONLY);
	return (fd);
}

int	is_max(char **split)
{
	int	x;

	x = 0;
	while (split[x])
	{
		if (ft_atoi(split[x]) < INT_MIN || ft_atoi(split[x]) > INT_MAX)
			return (1);
		x++;
	}
	return (0);
}

int	process_z_value(char *line, t_map *map, int x)
{
	char	**split;
	int		y;
	int		width;

	split = ft_split(line, ' ');
	if (!split)
		return (0);
	width = 0;
	while (split[width])
		width++;
	if (x == 0)
		map->width = width;
	if (width != map->width || is_max(split))
		return (ft_free_split(split), 0);
	map->z_matrix[x] = malloc(sizeof(int) * width);
	if (!map->z_matrix[x])
		return (ft_free_split(split), 0);
	y = -1;
	while (++y < width)
		map->z_matrix[x][y] = ft_atoi(split[y]);
	ft_free_split(split);
	return (1);
}
