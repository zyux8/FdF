/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaker <ohaker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 23:41:16 by ohaker            #+#    #+#             */
/*   Updated: 2025/05/12 17:53:21 by ohaker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

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

void	cleanup_and_exit(t_data *data)
{
	if (data->map->z_matrix)
		free_z_matrix(data->map->z_matrix, data->map->height);
	if (data->img)
		mlx_destroy_image(data->mlx, data->img);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	exit(0);
}

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
