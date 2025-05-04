/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaker <ohaker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:23:56 by ohaker            #+#    #+#             */
/*   Updated: 2025/05/04 21:17:06 by ohaker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	free_z_matrix(int **z_matrix, int rows)
{
	int	i;

	i = 0;
	while (i < rows)
	{
		free(z_matrix[i]);
		i++;
	}
	free(z_matrix);
}

int	ft_count_lines(int fd)
{
	int		count;
	char	*line;

	count = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		count++;
		free(line);
	}
	return (count);
}

int	height_reopen(char *file, t_map *map)
{
	int fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		printf("Error opening file: %s\n", file);
		return (0);
	}
	map->height = ft_count_lines(fd);
	close(fd);
	fd = open(file, O_RDONLY);
	return (fd);
}

void	handle_read_error(t_map *map, char *line, char **split, int row, char *error_msg)
{
	if (error_msg)
		printf("%s\n", error_msg);
	if (line)
		free(line);
	if (split)
		ft_free_split(split);
	if (map->z_matrix)
		free_z_matrix(map->z_matrix, row);
	map->z_matrix = NULL;
}

int	process_line(char *line, t_map *map, int x)
{
	char	**split;
	int		y;
	int		current_width;

	split = ft_split(line, ' ');
	if (!split)
		return (0);
	current_width = 0;
	while (split[current_width])
		current_width++;
	if (x == 0)
		map->width = current_width;
	else if (current_width != map->width)
	{
		ft_free_split(split);
		return (0);
	}
		map->z_matrix[x] = malloc(sizeof(int) * current_width);
	if (!map->z_matrix[x])
	{
		ft_free_split(split);
		return (0);
	}
	y = 0;
	while (y < current_width)
	{
		map->z_matrix[x][y] = ft_atoi(split[y]);
		y++;
	}
	ft_free_split(split);
	return (1);
}
