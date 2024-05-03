/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:44:30 by jcummins          #+#    #+#             */
/*   Updated: 2024/05/03 16:09:28 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void set_scale(t_map *map)
{
    float aspect_ratio;
    int base_scale_w;
    int base_scale_h;

    aspect_ratio = (float)map->width_x / (float)map->height_y;
    base_scale_w = RES_W / map->width_x;
    base_scale_h = RES_H / map->height_y;
    map->scale = (base_scale_w < base_scale_h) ? base_scale_w : base_scale_h;
	if (map->scale < 1)
		map->scale = 1;
    map->offset_x = (RES_W - (map->width_x * map->scale)) / 2;
    map->offset_y = (RES_H - (map->height_y * map->scale)) / 2;
}

int get_colour_arg(char *str)
{
	if (!ft_strncmp(str, "RED", 3))
		return (0x00FF0000);
	else
		return (0x00FFFFFF);
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
	point->c = map->c_default;
}

void	map_init(t_map *map)
{
	char			*line;
	char			**spline;
	unsigned int	x;
	unsigned int	y;

	map->points = malloc(sizeof(t_vector **) * map->height_y);
	if (!map->points)
		return ;
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
}

void	map_project(t_map *map)
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
			map->points[y][x]->py = ((map->scale / 2) * \
					(x + y)) + map->offset_y - map->points[y][x]->z;
			x++;
		}
		y++;
	}
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
	map->fd = open(map->name, O_RDONLY);
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
	map_project(map);
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
	draw_map(map, mlx);
	mlx_loop(mlx->mlx);
	/*mlx_destroy_window(mlx->mlx, mlx->win);*/
	mlx_destroy_display(mlx->mlx);
	free_map(map);
	free(mlx);
	return (0);
}
