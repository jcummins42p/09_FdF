/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:44:30 by jcummins          #+#    #+#             */
/*   Updated: 2024/04/29 20:37:15 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	map_init(t_map *map)
{
	char			*line;
	char			**spline;
	unsigned int	x;
	unsigned int	y;
	unsigned int	scale = 4;
	unsigned int	offset = 100;

	y = 0;
	map->points = malloc(sizeof (t_vector **));
	line = get_next_line(map->fd);
	while (y < map->height_y)
	{
		map->points[y] = malloc(sizeof(t_vector *) * map->width_x);
		spline = ft_split(line, ' ');
		x = 0;
		while (x < map->width_x)
		{
			map->points[y][x].x = (x * scale) + offset;
			map->points[y][x].y = (y * scale) + offset;
			map->points[y][x].z = ft_atoi(spline[x]);
			map->points[y][x].c = 0x00FF00FF;
			x++;
		}
		y++;
	}
}

void	draw_map(t_map *map)
{
	t_mlx_vars		*mlx;
	t_data			img;
	/*t_vector		*direction;*/
	/*t_vector		*origin;*/
	/*t_vector		*end;*/
	/*t_unit_vect		*unt_vec;*/
	unsigned int	x;
	unsigned int	y;

	mlx = malloc(sizeof(t_mlx_vars));
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, RES_W, RES_H, map->name);
	mlx_hook(mlx->win, 2, 1L<<0, mlx_close, &mlx);
	img.img = mlx_new_image(mlx->mlx, RES_W, RES_H);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	y = 0;
	map_init(map);
	while (y < map->height_y - 1)
	{
		x = 0;
		while (x < map->width_x - 1)
		{
			connect_points(img, &map->points[y][x], &map->points[y][x + 1]);
			connect_points(img, &map->points[y][x], &map->points[y + 1][x]);
			connect_points(img, &map->points[y][x], &map->points[y + 1][x + 1]);
			connect_points(img, &map->points[y + 1][x], &map->points[y][x + 1]);
			connect_points(img, &map->points[y + 1][x], &map->points[y + 1][x + 1]);
			connect_points(img, &map->points[y][x + 1], &map->points[y + 1][x + 1]);
			/*draw_circle(img, &map->points[y][x], 5, 0x00FF00FF);*/
			x++;
		}
		y++;
	}

	/*direction = new_vector(-30, -20, 0, 0);*/
	/*origin = new_vector(100, 100, 0, 0xFFFFFF00);*/
	/*end = new_vector(500, 300, 0, 0x00FF00FF);*/
	/*unt_vec = normalize_vector(direction);*/
	/*printf("Vector length is %f\n", vector_length(direction->x, direction->y));*/
	/*printf("Direction vector x = %d, y = %d\n", direction->x, direction->y);*/
	/*printf("Unit vector x = %f, y = %f\n", unt_vec->x, unt_vec->y);*/
	/*connect_points(img, origin, end);*/
	/*draw_circle(img, origin, 5, 0x00FF00FF);*/
	/*draw_circle(img, end, 5, 0x00FF00FF);*/
	mlx_put_image_to_window(mlx->mlx, mlx->win, img.img, 0, 0);
	mlx_loop(mlx->mlx);
}

int	set_dimensions(t_map *map)
{
	char			**split_line;
	char			*line;
	unsigned int	x;
	unsigned int	y;

	y = 0;
	map->width_x = 0;
	line = get_next_line(map->fd);
	while (line)
	{
		y++;
		x = 0;
		split_line = ft_split(line, ' ');
		while (split_line[x] != NULL)
			x++;
		if (map->width_x && map->width_x != x)
			return (0);
		map->width_x = x;
		line = get_next_line(map->fd);
	}
	map->height_y = y;
	close(map->fd);
	map->fd = open(map->name, O_RDONLY);
	return (1);
}

int	main(int argc, char *argv[])
{
	t_map	*map;

	map = malloc(sizeof (t_map));
	(void)argv;
	if (argc != 2)
	{
		ft_printf("Please provide a map file\n");
		return (1);
	}
	else
	{
		map->fd = open(argv[1], O_RDONLY);
		map->name = (argv[1]);
		if (!set_dimensions(map))
		{
			ft_printf("Invalid map file\n");
			return (1);
		}
		ft_printf("%s: %d x %d\n", map->name, map->height_y, map->width_x);
		draw_map(map);
	}
	return (0);
}
