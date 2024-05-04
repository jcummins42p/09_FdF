/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:44:30 by jcummins          #+#    #+#             */
/*   Updated: 2024/05/04 11:43:06 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void set_scale(t_map *map)
{
    int base_scale_w;
    int base_scale_h;
	/*int	grid_width;*/
	int	grid_height;

    base_scale_w = (RES_W / map->width_x) >> 1;
    base_scale_h = (RES_H / map->height_y);
	if (base_scale_w < base_scale_h)
	   	map->scale = base_scale_w;
	else
		map->scale = base_scale_h;
	if (map->scale < 1)
		map->scale = 1;
	/*grid_width = (map->width_x - map->height_y) * map->scale / 2;*/
	grid_height = (map->width_x + map->height_y) * map->scale / 4;
	map->offset_x = ((RES_W) / 2);
	map->offset_y = ((RES_H - grid_height) >> 1);
	if (map->scale == 1)
	{
		map->offset_x = ((RES_W) >> 1);
		map->offset_y = (RES_H - grid_height) >> 1;
	}
}

void	set_height_colour(t_map *map, t_vector *point, char *str)
{
	char	**spl_point;
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '\n' && str[i] != '-' && !ft_isdigit(str[i]))
		{
			spl_point = ft_split(str, ',');
			point->z = ft_atoi(spl_point[0]) * map->z_scale;
			point->c = ft_atoi_hex(spl_point[1]);
			free_split(spl_point);
			return ;
		}
		i++;
	}
	point->z = ft_atoi(str) * map->z_scale;
	point->c = colour_increment(map->c_default, point->z);
}

void	map_init(t_map *map)
{
	char			*line;
	char			**spline;
	unsigned int	x;
	unsigned int	y;

	map->fd = open(map->name, O_RDONLY);
	if (map->fd < 0)
		return ;
	map->points = malloc(sizeof(t_vector **) * map->height_y);
	if (!map->points)
	{
		close(map->fd);
		return ;
	}
	y = 0;
	line = get_next_line(map->fd);
	spline = ft_split(line, ' ');
	while (line && y < map->height_y)
	{
		map->points[y] = malloc(sizeof(t_vector *) * map->width_x);
		x = 0;
		while (x < map->width_x)
		{
			map->points[y][x] = malloc(sizeof(t_vector));
			map->points[y][x]->x = x;
			set_height_colour(map, map->points[y][x], spline[x]);
			map->points[y][x]->y = y;
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
	close(map->fd);
}

void	project_map(t_map *map)
{
	unsigned int	x;
	unsigned int	y;

	y = 0;
	while (y < map->height_y)
	{
		x = 0;
		while (x < map->width_x)
		{
			map->points[y][x]->px = map->scale * (x - y) + map->offset_x;
			map->points[y][x]->py = ((map->scale * \
					(x + y)) / 2) + map->offset_y - map->points[y][x]->z;
			x++;
		}
		y++;
	}
}

int	draw_pixel_map(t_map *map, t_mlx_vars *mlx)
{
	t_img_vars		img;
	unsigned int	x;
	unsigned int	y;

	ft_printf("Using more efficient pixel put\n");
	img.img = mlx_new_image(mlx->mlx, RES_W, RES_H);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	y = 0;
	while (y < map->height_y)
	{
		x = 0;
		while (x < map->width_x)
		{
			my_mlx_pixel_put(&img, map->points[y][x]->px, map->points[y][x]->py, map->points[y][x]->c);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->win, img.img, 0, 0);
	mlx_destroy_image(mlx->mlx, img.img);
	return (1);
}

int	draw_map(t_map *map, t_mlx_vars *mlx)
{
	t_img_vars		img;
	unsigned int	x;
	unsigned int	y;

	img.img = mlx_new_image(mlx->mlx, RES_W, RES_H);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	y = 0;
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
	mlx_destroy_image(mlx->mlx, img.img);
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
	close(map->fd);
	return (1);
}

int	main(int argc, char *argv[])
{
	t_map			*map;
	t_mlx_vars		*mlx;

	(void)argv;
	if (argc < 2)
	{
		ft_printf("Please provide a map file\n");
		return (1);
	}
	map = malloc(sizeof (t_map));
	if (!map)
		return (1);
	map->fd = open(argv[1], O_RDONLY);
	if (argc > 2)
	{
		map->z_scale = ft_atoi(argv[2]);
	}
	else
		map->z_scale = 1;
	if (argc > 3)
	{
		map->c_default = get_colour_arg(argv[3]);
	}
	else
		map->c_default = 0x00FFFFFF;
	if (map->fd < 0)
	{
		free (map);
		return (1);
	}
	map->name = (argv[1]);
	if (!set_dimensions(map))
	{
		ft_printf("Invalid map file\n");
		free(map);
		return (1);
	}
	set_scale(map);
	map_init(map);
	project_map(map);
	mlx = malloc(sizeof(t_mlx_vars));
	if (mlx == NULL)
	{
		close(map->fd);
		free_map(map);
		return (1);
	}
	mlx->mlx = mlx_init();
	if (mlx->mlx == NULL)
	{
		free(mlx);
		close(map->fd);
		free_map(map);
		return (1);
	}
	mlx->win = mlx_new_window(mlx->mlx, RES_W, RES_H, map->name);
	if (mlx->win == NULL)
	{
		mlx_destroy_display(mlx->mlx);
		free(mlx);
		close(map->fd);
		free_map(map);
		return (1);
	}
	mlx->map = map;
	mlx_loop_hook(mlx->mlx, &handle_no_event, mlx);
	mlx_hook(mlx->win, KeyPress, KeyPressMask, &handle_keypress, mlx);
	mlx_hook(mlx->win, KeyRelease, KeyReleaseMask, &handle_keyrelease, mlx);
	ft_printf("%s: %d x %d\n", map->name, map->height_y, map->width_x);
	if (map->scale > 1)
		draw_map(map, mlx);
	else
		draw_pixel_map(map, mlx);
	mlx_loop(mlx->mlx);
	mlx_destroy_display(mlx->mlx);
	free_map(map);
	free(mlx->mlx);
	free(mlx);
	return (0);
}
