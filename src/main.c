/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:44:30 by jcummins          #+#    #+#             */
/*   Updated: 2024/05/01 00:55:44 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	map_scale(t_map *map)
{
	(void)map;
	map->scale = RES_H / map->height_y;
	if (map->scale > RES_W / map->width_x)
		map->scale = RES_W / map->width_x;
	map->offset = map->scale;
}

void	map_init(t_map *map)
{
	char			*line;
	char			**spline;
	unsigned int	x;
	unsigned int	y;

	y = 0;
	map->points = malloc(sizeof(t_vector **) * map->height_y);
	line = get_next_line(map->fd);
	spline = ft_split(line, ' ');
	while (line && y < map->height_y)
	{
		map->points[y] = malloc(sizeof(t_vector *) * map->width_x);
		x = 0;
		while (x < map->width_x)
		{
			map->points[y][x] = malloc(sizeof(t_vector));
			map->points[y][x]->z = ft_atoi(spline[x]);
			map->points[y][x]->x = (x * map->scale) + map->offset;
			map->points[y][x]->y = (y * map->scale) + map->offset - map->points[y][x]->z;
			map->points[y][x]->c = 0x00aa00bbcc + (map->points[y][x]->z * 30);
			x++;
		}
		free(line);
		line = get_next_line(map->fd);
		free_split(spline);
		spline = ft_split(line, ' ');
		y++;
	}
	free(spline);
}

void	draw_map(t_map *map)
{
	t_mlx_vars		*mlx;
	t_data			img;
	unsigned int	x;
	unsigned int	y;

	mlx = malloc(sizeof(t_mlx_vars));
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, RES_W, RES_H, map->name);
	mlx_hook(mlx->win, 2, 1L << 0, mlx_close, mlx);
	img.img = mlx_new_image(mlx->mlx, RES_W, RES_H);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	y = 0;
	map_init(map);
	while (y < map->height_y - 1)
	{
		x = 0;
		while (x < map->width_x - 1)
		   {
			connect_points(img, map->points[y][x], map->points[y][x + 1]);
			connect_points(img, map->points[y][x], map->points[y + 1][x]);
			x++;
		}
		connect_points(img, map->points[y][x], map->points[y + 1][x]);
		y++;
	}
	x = 0;
	while (x < map->width_x - 1)
	{
		connect_points(img, map->points[y][x], map->points[y][x + 1]);
		x++;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->win, img.img, 0, 0);
	mlx_loop(mlx->mlx);
	free_map(map);
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
	if (!line)
		return (0);
	while (line)
	{
		y++;
		x = 0;
		split_line = ft_split(line, ' ');
		while (split_line[x] != NULL)
			x++;
		if (map->width_x && map->width_x != x)
		{
			free_split(split_line);
			free(line);
			return (0);
		}
		free_split(split_line);
		free(line);
		map->width_x = x;
		line = get_next_line(map->fd);
	}
	map->height_y = y;
	map_scale(map);
	close(map->fd);
	map->fd = open(map->name, O_RDONLY);
	return (1);
}

void	test_colourshift(void)
{
	t_mlx_vars		*mlx;
	t_data			img;
	t_vector		*a;
	t_vector		*b;

	a = malloc(sizeof(t_vector));
	b = malloc(sizeof(t_vector));
	a->x = 100;
	a->y = 100;
	a->c = 0x0000AA00;
	b->x = 400;
	b->y = 400;
	b->c = 0x00AA00AA;
	mlx = malloc(sizeof(t_mlx_vars));
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, RES_W, RES_H, "TESTWINDOW");
	mlx_hook(mlx->win, 2, 1L << 0, mlx_close, mlx);
	img.img = mlx_new_image(mlx->mlx, RES_W, RES_H);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);

	connect_points(img, a, b);
	mlx_put_image_to_window(mlx->mlx, mlx->win, img.img, 0, 0);
	mlx_loop(mlx->mlx);
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
