/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hookhandlers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:32:48 by jcummins          #+#    #+#             */
/*   Updated: 2024/05/21 14:32:03 by jcummins         ###   ########.fr       */
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

int	k_control(int keysym, t_mlx_vars *vars)
{
	if (keysym == XK_w || keysym == XK_s)
		k_tilt(keysym, vars);
	else if ((keysym >= XK_Left && keysym <= XK_Down) \
			|| keysym == XK_o || keysym == XK_i)
		k_dir_key(keysym, vars);
	else if ((keysym >= XK_0 && keysym <= XK_9) || keysym == XK_d)
		k_color_key(keysym, vars);
	else if ((keysym >= XK_q || keysym == XK_e))
		k_rotate(keysym, vars);
	else if (keysym == XK_n)
		vars->map->z_scale -= (0.01);
	else if (keysym == XK_m)
		vars->map->z_scale += (0.01);
	else if (keysym == XK_comma || keysym == XK_period)
		k_zoom(keysym, vars);
	else
		return (0);
	return (1);
}

int	k_press(int keysym, t_mlx_vars *vars)
{
	int	redraw;

	redraw = 0;
	if (keysym == XK_Escape)
		mlx_destroy_window(vars->mlx, vars->win);
	else
		redraw = k_control(keysym, vars);
	ft_printf("Keypress: %d\n", keysym);
	if (redraw)
	{
		project_map(vars->map);
		draw_map(vars->map, vars);
	}
	return (0);
}
