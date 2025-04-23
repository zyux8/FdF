/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaker <ohaker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 22:09:53 by ohaker            #+#    #+#             */
/*   Updated: 2025/04/15 22:09:54 by ohaker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int main(void)
{
	void *mlx;
	void *mlx_win;
	t_data img;
	t_data img2;
	int x;
	int y;

	x = 0;
	y = 0;
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
	img.img = mlx_new_image(mlx, 1920, 1080);
	img2.img = mlx_new_image(mlx, 1920, 700);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	img2.addr = mlx_get_data_addr(img2.img, &img2.bits_per_pixel, &img2.line_length, &img2.endian);
	while (x <= 1920 && y <= 1080)
	{
		my_pixel_put(&img, x, y, 0x000000FF);
		x++;
		my_pixel_put(&img, x, y, 0x00FF0000);
		x++;
		my_pixel_put(&img, x, y, 0x0000FF00);
		x++;
		if (x == 1920)
		{
			y++;
			x = 0;
		}
	}
	x = 0;
	y = 300;
	while (x <= 1920)
	{
		my_pixel_put(&img2, x, y, 0x0000FF00);
		x++;
	}
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_put_image_to_window(mlx, mlx_win, img2.img, 0, 300);
	mlx_loop(mlx);
}