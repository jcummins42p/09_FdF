/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:44:30 by jcummins          #+#    #+#             */
/*   Updated: 2024/04/25 21:44:39 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	draw_horizontal_line(t_data img, int y)
{
	int	x;

	x = 0;
	while (x < 500)
		my_mlx_pixel_put(&img, x++, y, 0x00FF0000);
}

void	draw_vertical_line(t_data img, int x)
{
	int	y;

	y = 30;
	while (y < 500)
		my_mlx_pixel_put(&img, x, y++, 0x00FF0000);
}

//	takes two position vectors and returns the length
float	vector_length(int x, int y)
{
	return (sqrtf((x * x) + (y * y)));
}

float	norm_vd(t_vector *direction, int dimension)
{
	float	v_len;

	v_len = vector_length(direction->x, direction->y);
	if(v_len > 0)
		return (dimension / v_len);
	else
		return (0);
}

void	draw_line(t_data img, t_vector *origin, t_vector *direction)
{
	float	dx = norm_vd(direction, direction->x);
	float	dy = norm_vd(direction, direction->y);
	int	i;

	i = 0;
	while (i * dy <= direction->y)
	{
		my_mlx_pixel_put(&img, (origin->x + (i * dx)), (origin->y + (i * dy)), 0x00FF0000);
		i++;
	}
}

t_unit_vect	*normalize_vector(t_vector *direction)
{
	t_unit_vect	*output;
	float		v_len;

	output = malloc(sizeof(t_unit_vect));
	if (!output)
		return (NULL);
	v_len = vector_length(direction->x, direction->y);
	if (v_len > 0)
	{
		output->x = direction->x / v_len;
		output->y = direction->y / v_len;
		output->z = direction->z / v_len;
	}
	return (output);
}

t_vector	*new_vector(int x, int y, int z, int c)
{
	t_vector	*output;

	output = malloc(sizeof(t_vector));
	if (!output)
		return (NULL);
	output->x = x;
	output->y = y;
	output->z = z;
	output->c = c;
	return (output);
}

void	draw_map(int map_fd)
{
	void			*mlx;
	t_data			img;
	void			*mlx_win;
	t_vector		*direction;
	t_vector		*origin;
	t_unit_vect		*unt_vec;

	(void)map_fd;
	direction = new_vector(300, 400, 0, 0);
	origin = new_vector(0, 0, 0, 0);
	unt_vec = normalize_vector(direction);
	printf("Vector length is %f\n", vector_length(direction->x, direction->y));
	printf("Direction vector x = %d, y = %d\n", direction->x, direction->y);
	printf("Unit vector x = %f, y = %f\n", unt_vec->x, unt_vec->y);
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 786, 540, "Hello World!");
	img.img = mlx_new_image(mlx, 768, 540);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	draw_line(img, origin, direction);
	/*draw_horizontal_line(img, 45);*/
	/*draw_vertical_line(img, 300);*/
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
		draw_map(map_fd);
	}
	return (0);
}
