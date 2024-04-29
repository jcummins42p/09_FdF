/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:44:30 by jcummins          #+#    #+#             */
/*   Updated: 2024/04/30 00:05:48 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	map_init(t_map *map)
{
	char			*line;
	char			**spline;
	unsigned int	x;
	unsigned int	y;
	unsigned int	scale = 2;
	unsigned int	offset = 50;

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
			draw_circle(img, &map->points[y][x], 5, 0x00FF00FF);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->win, img.img, 0, 0);
	mlx_loop(mlx->mlx);
}

void	free_split(char **split)
{
	char	**head;

	if (!split)
		return ;
	head = split;
	while (*split)
	{
		free(*split);
		split++;
	}
	free(head);
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
		free(line);
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
