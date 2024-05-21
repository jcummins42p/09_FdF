/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 11:18:30 by jcummins          #+#    #+#             */
/*   Updated: 2024/05/21 14:39:39 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	set_defaults(t_map *map, char **argv)
{
	map->fd = open(argv[1], O_RDONLY);
	if (map->fd < 0)
		return (0);
	map->name = (argv[1]);
	map->z_scale = 0.1;
	map->c_default = 0x00FFFFFF;
	map->angle = 2.0;
	map->rotate = 0;
	return (1);
}

int	set_scale(t_map *map)
{
	int	base_scale_w;
	int	base_scale_h;
	int	grid_height;

	base_scale_w = (RES_W / map->width_x) >> 1;
	base_scale_h = (RES_H / map->height_y);
	if (base_scale_w < base_scale_h)
		map->scale = base_scale_w;
	else
		map->scale = base_scale_h;
	if (map->scale < 1)
		map->scale = 1;
	grid_height = (map->width_x + map->height_y) * map->scale / 4;
	map->offset_x = ((RES_W) >> 1);
	map->offset_y = ((RES_H - grid_height) >> 2);
	if (map->scale == 1)
	{
		map->offset_x = ((RES_W) >> 1);
		map->offset_y = (RES_H - grid_height) >> 1;
	}
	return (1);
}

int	set_dimensions(t_map *map)
{
	char			**split_line;
	char			*line;

	map->y = 0;
	map->width_x = 0;
	line = get_next_line(map->fd);
	if (!line)
		return (0);
	while (line)
	{
		map->y++;
		map->x = 0;
		split_line = ft_split(line, ' ');
		while (split_line[map->x] != NULL)
			map->x++;
		free_split(split_line);
		free(line);
		if (map->width_x && map->width_x != map->x)
			return (0);
		map->width_x = map->x;
		line = get_next_line(map->fd);
	}
	map->height_y = map->y;
	close(map->fd);
	return (1);
}

int	map_assign(t_map *map, char *line, char **spline)
{
	map->y = 0;
	while (line && map->y < map->height_y)
	{
		map->points[map->y] = malloc(sizeof(t_vector *) * map->width_x);
		map->x = 0;
		while (map->x < map->width_x)
		{
			map->points[map->y][map->x] = malloc(sizeof(t_vector));
			map->points[map->y][map->x]->x = map->x;
			set_height_colour(map, map->points[map->y][map->x], spline[map->x]);
			map->points[map->y][map->x]->y = map->y;
			map->x++;
		}
		free(line);
		free_split(spline);
		line = get_next_line(map->fd);
		spline = ft_split(line, ' ');
		map->y++;
	}
	free(line);
	free_split(spline);
	return (1);
}

int	map_init(t_map *map)
{
	char			*line;
	char			**spline;

	map->fd = open(map->name, O_RDONLY);
	if (map->fd < 0)
		return (0);
	map->points = malloc(sizeof(t_vector **) * map->height_y);
	if (!map->points)
	{
		close(map->fd);
		return (0);
	}
	else
	{
		line = get_next_line(map->fd);
		spline = ft_split(line, ' ');
		map_assign(map, line, spline);
	}
	close(map->fd);
	return (1);
}
