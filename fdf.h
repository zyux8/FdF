/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaker <ohaker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 19:11:02 by ohaker            #+#    #+#             */
/*   Updated: 2025/04/26 19:09:08 by ohaker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(FDF_H)
#define FDF_H

typedef struct	s_data 
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

// typedef struct s_matrix
// {
// 	int x;
// 	int y;
// 	int z;
// }	t_matrix;

typedef struct s_map
{
	int		width;
	int		height;
	int		**z_matrix;
}	t_map;

typedef struct s_vars
{
	void	*mlx;
	void	*win;
	void	*img;
}	t_vars;

# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080

# include "libft/libft.h"
# include "get_next_line/get_next_line.h"
# include "minilibx-linux/mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

void	draw_line(t_data *data, int xS, int yS, int xE, int yE, int color);
void	my_pixel_put(t_data *data, int x, int y, int color);
int		ft_count_lines(int fd);
int		get_width(char *line);
void	read_map(int fd, t_map *map);
int		main(void);

#endif // FDF_H
