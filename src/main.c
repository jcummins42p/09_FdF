/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:44:30 by jcummins          #+#    #+#             */
/*   Updated: 2024/04/26 17:32:16 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_map(int map_fd, char *map_name)
{
	void			*mlx;
	t_data			img;
	void			*mlx_win;
	t_vector		*direction;
	t_vector		*origin;
	t_vector		*end;
	t_unit_vect		*unt_vec;
	char			*window_name;

	window_name = ft_strjoin("fdf: ", map_name);
	(void)map_fd;
	direction = new_vector(-30, -20, 0, 0);
	origin = new_vector(100, 100, 0, 0xFFFFFF00);
	end = new_vector(500, 300, 0, 0x00FF00FF);
	unt_vec = normalize_vector(direction);
	printf("Vector length is %f\n", vector_length(direction->x, direction->y));
	printf("Direction vector x = %d, y = %d\n", direction->x, direction->y);
	printf("Unit vector x = %f, y = %f\n", unt_vec->x, unt_vec->y);
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, RES_W, RES_H, window_name);
	img.img = mlx_new_image(mlx, RES_W, RES_H);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	connect_points(img, origin, end);
	draw_circle(img, origin, 5, 0x00FF00FF);
	draw_circle(img, end, 5, 0x00FF00FF);
	/*draw_lline(img, origin, direction, 20);*/
	/*draw_horizontal_line(img, 400, 60, -450);*/
	/*draw_vertical_line(img, 500, 60, -380);*/
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}

int	main(int argc, char *argv[])
{
	int	map_fd;

	(void)argv;
	if (argc != 2)
	{
		ft_printf("Please provide a map file\n");
		return (1);
	}
	else
	{
		map_fd = open(argv[1], O_RDONLY);
		draw_map(map_fd, argv[1]);
	}
	return (0);
}
