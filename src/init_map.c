/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 11:18:30 by jcummins          #+#    #+#             */
/*   Updated: 2024/05/20 17:25:31 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	set_scale(t_map *map)
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
	/*map->offset_x = ((RES_W) / 2);*/
	map->offset_x = ((RES_W) >> 1);
	map->offset_y = ((RES_H - grid_height) >> 2);
	if (map->scale == 1)
	{
		map->offset_x = ((RES_W) >> 1);
		map->offset_y = (RES_H - grid_height) >> 1;
	}
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
