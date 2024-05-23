/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hookhandle_kb.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:32:48 by jcummins          #+#    #+#             */
/*   Updated: 2024/05/23 17:50:24 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	k_no_event(void *vars)
{
	(void) vars;
	return (0);
}

int	k_release(int keysym, void *vars)
{
	ft_printf("Keyrelease: %d\n", keysym);
	(void) vars;
	return (0);
}

void	k_rescale(int keysym, t_mlx_vars *vars)
{
	if (keysym == XK_n)
		vars->map->z_scale -= (0.01);
	else if (keysym == XK_m)
		vars->map->z_scale += (0.01);
	reset_colourscale(vars->map);
}

int	k_control(int keysym, t_mlx_vars *vars)
{
	if (keysym == XK_d)
		k_defaults(keysym, vars);
	else if ((keysym >= XK_Left && keysym <= XK_Down) \
			|| keysym == XK_o || keysym == XK_i)
		k_dir_key(keysym, vars);
	else if ((keysym >= XK_0 && keysym <= XK_9))
	{
		ft_printf("Should be changing color");
		k_color_key(keysym, vars);
	}
	else if (keysym == XK_t)
		toggle_default_colour(vars->map);
	else if (keysym == XK_q || keysym == XK_e \
			|| keysym == XK_s || keysym == XK_w)
		k_tilt_rotate(keysym, vars);
	else if (keysym == XK_n || keysym == XK_m)
		k_rescale(keysym, vars);
	else if (keysym == XK_comma || keysym == XK_period)
		k_zoom(keysym, vars);
	else if (keysym == XK_x || keysym == XK_z)
		k_zshift_radius(keysym, vars);
	else
		return (0);
	return (1);
}

int	k_press(int keysym, t_mlx_vars *vars)
{
	int	redraw;

	redraw = 0;
	if (keysym == XK_Escape)
	{
		ft_printf("escape pressed\n");
		mlx_loop_end(vars->mlx);
	}
	else if (keysym == XK_c)
		christmas(keysym, vars);
	else
		redraw = k_control(keysym, vars);
	ft_printf("Keypress: %d\n", keysym);
	if (redraw)
	{
		reset_colourscale(vars->map);
		project_map(vars->map);
		draw_map(vars->map, vars);
		display_hud(vars);
	}
	return (0);
}
