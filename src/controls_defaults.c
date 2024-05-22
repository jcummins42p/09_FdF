/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls_defaults.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 13:48:27 by jcummins          #+#    #+#             */
/*   Updated: 2024/05/22 14:27:59 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	k_defaults(int keysym, t_mlx_vars *vars)
{
	(void)keysym;
	ft_printf("Attempting to change defaults");
	vars->map->c_default = 0x00224488;
	reset_heightmap(vars->map);
}

void	reset_heightmap(t_map *map)
{
	t_vector	*point;

	map->y = 0;
	while (map->y < map->height_y)
	{
		map->x = 0;
		while (map->x < map->width_x)
		{
			point = map->points[map->y][map->x];
			point->z = point->file_z;
			map->x++;
		}
		map->y++;
	}
}
