/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaker <ohaker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 19:11:02 by ohaker            #+#    #+#             */
/*   Updated: 2025/05/12 01:58:57 by ohaker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(FDF_H)
#define FDF_H

typedef struct s_map
{
	int		width;
	int		height;
	int		**z_matrix;
	int 	offset_x;
	int 	offset_y;
	int 	color;
	int		scale;
	int		z_scale;
	// float	angle_z;
}	t_map;

typedef struct	s_data 
{
	void	*img;
	void	*mlx;
	void	*win;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	t_map	*map;
}	t_data;

typedef struct s_point
{
	int x;
	int y;
	int z;
	int iso_x;
	int iso_y;
}	t_point;

typedef struct s_draw
{
	int diffx;
	int diffy;
	int step_x;
	int step_y;
	int err;
	int e2;
}	t_draw;

typedef struct s_iso
{
	float angle;
	float centered_x;
	float centered_y;
	float projected_x;
	float projected_y;
}	t_iso;

# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080
# define KEY_ESC 65307
# define KEY_J 106
# define KEY_K 107
# define KEY_I 105
# define KEY_O 111
# define KEY_N 110
# define KEY_M 109
#ifndef PI
    #define PI 3.14159265358979323846
#endif

# include "libft/libft.h"
# include "get_next_line/get_next_line.h"
# include "ft_printf/ft_printf.h"
# include "minilibx-linux/mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>

void	draw_line(t_data *data, t_point *p1, t_point *p2, int color);
void	my_pixel_put(t_data *data, int x, int y, int color);
int		ft_count_lines(int fd);
void	calculate_iso(t_map *map, t_point *point);
void	read_map(char *file, t_map *map);
int		main(int argc, char **argv);
void	draw_map(t_data *data, t_map *map);
void	free_z_matrix(int **z_matrix, int rows);
void	get_color(t_map *map, int z);
void	update_line_drawing(t_draw *draw, t_point *p1);
int		height_reopen(char *file, t_map *map);
void	handle_read_error(t_map *map, char *line, char **split, int row);
int		process_z_value(char *line, t_map *map, int x);
int		handle_destroy(t_data *data);
void	cleanup_and_exit(t_data *data);
void	redraw_map(t_data *data);
int		handle_key(int keycode, t_data *data);
void	init_data(t_data *data, t_map *map);
int		alloc_z_matrix(t_map *map);
void	process_lines(int fd, t_map *map);
void	draw_segment(t_data *data, t_map *map, t_point *p1, t_point *p2);
void	draw_point_links(t_data *data, t_map *map, int x, int y);
// void	rotate_z(t_point *p, float angle, t_map *map);
void 	cleanup_and_exit(t_data *data);

#endif // FDF_H
