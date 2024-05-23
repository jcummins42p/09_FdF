/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:41:50 by jcummins          #+#    #+#             */
/*   Updated: 2024/05/23 17:02:04 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	display_hud(t_mlx_vars *mlx)
{
	mlx_string_put(mlx->mlx, mlx->win, 50, 50, DEF_C, mlx->map->name);
	mlx_string_put(mlx->mlx, mlx->win, 50, 70, DEF_C, \
			"i/o: Select inverted	or original controls");
	mlx_string_put(mlx->mlx, mlx->win, 50, 90, DEF_C, "q/e: Rotate");
	mlx_string_put(mlx->mlx, mlx->win, 50, 110, DEF_C, "w/s: Alter tilt angle");
	mlx_string_put(mlx->mlx, mlx->win, 50, 130, DEF_C, \
			"t: Toggle between colour modes");
	mlx_string_put(mlx->mlx, mlx->win, 50, 150, DEF_C, \
			"0-9: Choose alt colour");
	mlx_string_put(mlx->mlx, mlx->win, 50, 170, DEF_C, \
			"d: Reset to default heights");
	mlx_string_put(mlx->mlx, mlx->win, 50, 190, DEF_C, \
			"Left Mouse: Increase node height");
	mlx_string_put(mlx->mlx, mlx->win, 50, 210, DEF_C, \
			"Right Mouse: Decrease node height");
	mlx_string_put(mlx->mlx, mlx->win, 50, 230, DEF_C, \
			"Mouse Wheel: Zoom in/out");
	mlx_string_put(mlx->mlx, mlx->win, 50, 250, DEF_C, \
			"Side Mouse: Decrease/Increase brush strength");
	mlx_string_put(mlx->mlx, mlx->win, 50, 270, DEF_C, \
			"z/x: Decrease/Increase brush radius");
	mlx_string_put(mlx->mlx, mlx->win, 50, 290, DEF_C, \
			"n/m: Decrease/Increase heightmap multiplier");
	mlx_string_put(mlx->mlx, mlx->win, 50, 310, DEF_C, \
			"Number Keys will not work unless setxkbmap is set to us");
}
