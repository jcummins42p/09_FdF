/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funcs_controls.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 11:52:08 by jcummins          #+#    #+#             */
/*   Updated: 2024/05/21 14:31:38 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	k_color_key(int keysym, t_mlx_vars *vars)
{
	free_map(vars->map);
	if (keysym == XK_1)
		vars->map->c_default = 0x00FF0000;
	else if (keysym == XK_2)
		vars->map->c_default = 0x00FF8800;
	else if (keysym == XK_3)
		vars->map->c_default = 0x00FFFF00;
	else if (keysym == XK_4)
		vars->map->c_default = 0x0088FF00;
	else if (keysym == XK_5)
		vars->map->c_default = 0x0000FF00;
	else if (keysym == XK_6)
		vars->map->c_default = 0x0000FF88;
	else if (keysym == XK_7)
		vars->map->c_default = 0x0000FFFF;
	else if (keysym == XK_8)
		vars->map->c_default = 0x000088FF;
	else if (keysym == XK_9)
		vars->map->c_default = 0x000000FF;
	else if (keysym == XK_0)
		vars->map->c_default = 0x00FF00FF;
	else
		vars->map->c_default = 0x00FFFFFF;
	map_init(vars->map);
}

void	k_dir_key(int keysym, t_mlx_vars *vars)
{
	static int	inverted = 1;

	if (keysym == XK_i)
		inverted = 1;
	else if (keysym == XK_o)
		inverted = -1;
	if (keysym == XK_Left)
		vars->map->offset_x += 10 * inverted;
	else if (keysym == XK_Right)
		vars->map->offset_x -= 10 * inverted;
	else if (keysym == XK_Up)
		vars->map->offset_y += 10 * inverted;
	else if (keysym == XK_Down)
		vars->map->offset_y -= 10 * inverted;
}

void	k_zoom(int keysym, t_mlx_vars *vars)
{
	if (keysym == XK_period)
	{
		vars->map->scale += 1;
		vars->map->offset_y -= sqrt(vars->map->scale);
		vars->map->offset_x -= sqrt(vars->map->scale);
	}
	else if (keysym == XK_comma)
	{
		if (vars->map->scale > 1)
		{
			vars->map->scale -= 1;
		}
	}
}

void	k_rotate(int keysym, t_mlx_vars *vars)
{
	if (keysym == XK_q)
		vars->map->rotate += 0.01;
	else if (keysym == XK_e)
		vars->map->rotate -= 0.01;
}

void	k_tilt(int keysym, t_mlx_vars *vars)
{
	if (keysym == XK_s)
	{
		if (vars->map->angle < 100)
		{
			vars->map->angle *= 1.1;
		}
	}
	else if (keysym == XK_w)
	{
		if (vars->map->angle > 2)
		{
			vars->map->angle /= 1.1;
		}
	}
}
