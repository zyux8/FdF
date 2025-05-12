/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaker <ohaker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:23:56 by ohaker            #+#    #+#             */
/*   Updated: 2025/05/11 18:23:21 by ohaker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	free_z_matrix(int **z_matrix, int rows)
{
	int	x;

	x = 0;
	while (x < rows)
	{
		free(z_matrix[x]);
		x++;
	}
	free(z_matrix);
}

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

void	handle_read_error(t_map *map, char *line, char **split, int row)
{
	if (line)
		free(line);
	if (split)
		ft_free_split(split);
	if (map->z_matrix)
		free_z_matrix(map->z_matrix, row);
	map->z_matrix = NULL;
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
	if (width != map->width)
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
