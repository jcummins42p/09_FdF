/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   christmas.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:24:03 by jcummins          #+#    #+#             */
/*   Updated: 2024/05/23 17:47:36 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	imgflush(t_mlx_vars *vars)
{
	reset_colourscale(vars->map);
	project_map(vars->map);
	draw_map(vars->map, vars);
	display_hud(vars);
}

void	christmas(int keysym, t_mlx_vars *vars)
{
	int i;

	i = 0;
	(void)keysym;
	while(i < 3)
	{
		vars->map->c_default = 0x00FF0000;
		imgflush(vars);
		vars->map->c_default = 0x00FF8800;
		imgflush(vars);
		vars->map->c_default = 0x00FFFF00;
		imgflush(vars);
		vars->map->c_default = 0x0088FF00;
		imgflush(vars);
		vars->map->c_default = 0x0000FF00;
		imgflush(vars);
		vars->map->c_default = 0x0000FF88;
		imgflush(vars);
		vars->map->c_default = 0x0000FFFF;
		imgflush(vars);
		vars->map->c_default = 0x000088FF;
		imgflush(vars);
		vars->map->c_default = 0x000000FF;
		imgflush(vars);
		vars->map->c_default = 0x00FF00FF;
		imgflush(vars);
		i++;
	}
}
