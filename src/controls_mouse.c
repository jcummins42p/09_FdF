/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls_mouse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 13:09:12 by jcummins          #+#    #+#             */
/*   Updated: 2024/05/22 15:56:12 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	b_zshift(int button, int x, int y, t_mlx_vars *vars)
{
	t_vector	*point;
	t_map		*map;
	int			z_rad;

	button = (2 - button) * vars->map->z_brush;
	z_rad = vars->map->z_rad * vars->map->scale;
	map = vars->map;
	map->y = 0;
	ft_printf("colourshift x = %d, y = %d", x, y);
	while (map->y < map->height_y)
	{
		map->x = 0;
		while (map->x < map->width_x)
		{
			point = map->points[map->y][map->x];
			if (point->px < x + z_rad && point->px > x - z_rad \
					&& point->py < y + z_rad && point->py > y - z_rad)
			{
				point->z += button;
			}
			map->x++;
		}
		map->y++;
	}
}

void	b_zshift_strength(int button, int x, int y, t_mlx_vars *vars)
{
	(void)x;
	(void)y;
	if (button == 9)
		vars->map->z_brush += 1;
	else if (button == 8 && vars->map->z_brush > 1)
		vars->map->z_brush -= 1;
}
