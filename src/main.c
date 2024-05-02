/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:44:30 by jcummins          #+#    #+#             */
/*   Updated: 2024/05/02 17:43:12 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	map_scale(t_map *map)
{
	(void)map;
	map->scale = 2 * (RES_H / (map->height_y + map->width_x));
	/*if (map->scale > (RES_W / map->width_x))*/
		/*map->scale = (RES_W / map->width_x);*/
	map->offset_x = RES_W >> 1;
	map->offset_y = map->scale;
}

void	get_colour(t_vector *point, char *str)
{
	char	**spl_point;
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '\n' && str[i] != '-' && !ft_isdigit(str[i]))
		{
			spl_point = ft_split(str, ',');
			point->z = ft_atoi(spl_point[0]);
			point->c = ft_atoi_hex(spl_point[1]);
			free_split(spl_point);
			return ;
		}
		i++;
	}
	point->z = ft_atoi(str);
	point->c = 0x00FFFFFF;
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
			map->points[y][x]->x = (x * map->scale) - (y * map->scale) + map->offset_x;
			get_colour(map->points[y][x], spline[x]);
			map->points[y][x]->y = ((map->scale / 2) * (x + y)) + map->offset_y - map->points[y][x]->z;
			x++;
		}
		free(line);
		free_split(spline);
		line = get_next_line(map->fd);
		spline = ft_split(line, ' ');
		y++;
	}
	free(line);
	free_split(spline);
}

int	draw_map(t_map *map)
{
	t_mlx_vars		*mlx;
	t_img_vars		img;
	unsigned int	x;
	unsigned int	y;

	mlx = malloc(sizeof(t_mlx_vars));
	mlx->mlx = mlx_init();
	if (mlx->mlx == NULL)
		return (0);
	mlx->win = mlx_new_window(mlx->mlx, RES_W, RES_H, map->name);
	if (mlx->win == NULL)
	{
		free(mlx->win);
		return (0);
	}
	mlx_loop_hook(mlx->mlx, &handle_no_event, mlx);
	mlx_hook(mlx->win, KeyPress, KeyPressMask, &handle_keypress, mlx);
	mlx_hook(mlx->win, KeyRelease, KeyReleaseMask, &handle_keyrelease, mlx);
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
	mlx_destroy_image(mlx->mlx, img.img);
	mlx_destroy_display(mlx->mlx);
	free_map(map);
	free(mlx);
	return (1);
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

int	main(int argc, char *argv[])
{
	t_map	*map;

	(void)argv;
	if (argc != 2)
	{
		ft_printf("Please provide a map file\n");
		return (1);
	}
	else
	{
		map = malloc(sizeof (t_map));
		map->fd = open(argv[1], O_RDONLY);
		map->name = (argv[1]);
		if (!set_dimensions(map))
		{
			ft_printf("Invalid map file\n");
			free(map);
			return (1);
		}
		ft_printf("%s: %d x %d\n", map->name, map->height_y, map->width_x);
		draw_map(map);
	}
	return (0);
}
