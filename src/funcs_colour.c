/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funcs_colour.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 16:11:00 by jcummins          #+#    #+#             */
/*   Updated: 2024/05/22 14:58:23 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	colour_components(t_vector *vector)
{
	vector->c_red = vector->c >> 16;
	vector->c_grn = vector->c >> 8 & 0xFF;
	vector->c_blu = vector->c & 0xFF;
}

int	colour_gradient(t_vector *origin, t_vector *end, float ratio)
{
	int	red;
	int	grn;
	int	blu;
	int	out;

	red = fmin(fmax(0, (int)origin->c_red + \
				(end->c_red - origin->c_red) * ratio), 255);
	grn = fmin(fmax(0, (int)origin->c_grn + \
				(end->c_grn - origin->c_grn) * ratio), 255);
	blu = fmin(fmax(0, (int)origin->c_blu + \
				(end->c_blu - origin->c_blu) * ratio), 255);
	out = (red << 16) | (grn << 8) | blu;
	return (out);
}

int	colour_increment(int origin, int increment)
{
	int	red;
	int	grn;
	int	blu;
	int	out;

	red = fmin(fmax(0, (origin >> 16) + (increment << 5)), 255);
	grn = fmin(fmax(0, (origin >> 8 & 0xFF) + (increment << 5)), 255);
	blu = fmin(fmax(0, (origin & 0xFF) + (increment << 5)), 255);
	out = (red << 16) | (grn << 8) | blu;
	return (out);
}

void	reset_colourscale(t_map *map)
{
	t_vector	*point;

	map->y = 0;
	while (map->y < map->height_y)
	{
		map->x = 0;
		while (map->x < map->width_x)
		{
			point = map->points[map->y][map->x];
			if (!point->file_colour || map->c_toggle)
			{
				point->c = colour_increment(map->c_default, \
					(int)(point->z * map->z_scale));
			}
			map->x++;
		}
		map->y++;
	}
}

void	toggle_default_colour(t_map *map)
{
	t_vector		*point;

	map->y = 0;
	while (map->y < map->height_y)
	{
		map->x = 0;
		while (map->x < map->width_x)
		{
			point = map->points[map->y][map->x];
			if (!map->c_toggle || !point->file_colour)
			{
				point->c = colour_increment(map->c_default, \
					(int)(point->z * map->z_scale));
			}
			else
				point->c = point->file_colour;
			map->x++;
		}
		map->y++;
	}
	if (map->c_toggle)
		map->c_toggle = 0;
	else
		map->c_toggle = 1;
}
/*int	get_colour_arg(char *str)*/
/*{*/
	/*if (!ft_strnicmp(str, "RED", 3))*/
		/*return (0x00FF0000);*/
	/*if (!ft_strnicmp(str, "GREEN", 3))*/
		/*return (0x0000FF00);*/
	/*if (!ft_strnicmp(str, "BLUE", 3))*/
		/*return (0x000000FF);*/
	/*if (!ft_strnicmp(str, "CYAN", 3))*/
		/*return (0x0000FFFF);*/
	/*if (!ft_strnicmp(str, "MAGENTA", 3))*/
		/*return (0x00FF00FF);*/
	/*if (!ft_strnicmp(str, "YELLOW", 3))*/
		/*return (0x00FFFF00);*/
	/*if (!ft_strnicmp(str, "RED", 3))*/
		/*return (0x0000FFFF);*/
	/*if (!ft_strnicmp(str, "BLACK", 3))*/
		/*return (0x00222222);*/
	/*else*/
		/*return (0x00FFFFFF);*/
/*}*/
