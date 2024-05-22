/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hookhandle_mouse.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:32:48 by jcummins          #+#    #+#             */
/*   Updated: 2024/05/22 16:00:34 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	b_no_event(void *vars)
{
	(void) vars;
	return (0);
}

int	b_release(int button, void *vars)
{
	ft_printf("Mouserelease: %d\n", button);
	(void) vars;
	return (0);
}

void	b_zoom(int button, t_mlx_vars *vars)
{
	if (button == ON_MOUSEDOWN)
	{
		vars->map->scale += 1;
		vars->map->offset_y -= sqrt(vars->map->scale);
	}
	else if (button == ON_MOUSEUP)
	{
		if (vars->map->scale > 1)
		{
			vars->map->scale -= 1;
			vars->map->offset_y += sqrt(vars->map->scale);
		}
	}
}

int	b_control(int button, int x, int y, t_mlx_vars *vars)
{
	if (button == ON_MOUSEUP || button == ON_MOUSEDOWN)
		b_zoom(button, vars);
	else if (button == 1 || button == 3)
		b_zshift(button, x, y, vars);
	else if (button == 8 || button == 9)
		b_zshift_strength(button, x, y, vars);
	else
		return (0);
	return (1);
}

int	b_press(int button, int x, int y, t_mlx_vars *vars)
{
	int	redraw;

	(void)x;
	(void)y;
	redraw = 0;
	ft_printf("Keypress: %d\n", button);
	if (button == ON_DESTROY)
		mlx_destroy_window(vars->mlx, vars->win);
	else
		redraw = b_control(button, x, y, vars);
	if (redraw)
	{
		reset_colourscale(vars->map);
		project_map(vars->map);
		draw_map(vars->map, vars);
		display_hud(vars);
	}
	return (0);
}
