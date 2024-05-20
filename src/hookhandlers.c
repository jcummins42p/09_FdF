/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hookhandlers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:32:48 by jcummins          #+#    #+#             */
/*   Updated: 2024/05/20 17:58:40 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	handle_no_event(void *vars)
{
	(void) vars;
	return (0);
}

int	handle_keyrelease(int keysym, void *vars)
{
	ft_printf("Keyrelease: %d\n", keysym);
	(void) vars;
	return (0);
}

void	handle_color_key(int keysym, t_mlx_vars *vars)
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

void	handle_dir_key(int keysym, t_mlx_vars *vars)
{
	static int inverted = 1;

	if (keysym == XK_i)
		inverted = 1;
	else if (keysym == XK_o)
		inverted = -1;
	if (keysym == XK_Left)
		vars->map->offset_x += (vars->map->scale * inverted);
	else if (keysym == XK_Right)
		vars->map->offset_x -= (vars->map->scale * inverted);
	else if (keysym == XK_Up)
		vars->map->offset_y += (vars->map->scale * inverted);
	else if (keysym == XK_Down)
		vars->map->offset_y -= (vars->map->scale * inverted);
}

void	handle_zoom(int keysym, t_mlx_vars *vars)
{
	if (keysym == XK_period)
	{
		vars->map->scale += 1;
		vars->map->offset_y	-= sqrt(vars->map->scale);
		vars->map->offset_x	-= sqrt(vars->map->scale);
	}
	else if (keysym == XK_comma)
	{
		if (vars->map->scale > 1)
		{
			vars->map->scale -= 1;
			vars->map->offset_y	+= sqrt(vars->map->scale);
			vars->map->offset_x	+= sqrt(vars->map->scale);
		}
	}
}

void	handle_rotate(int keysym, t_mlx_vars *vars)
{
	if (keysym == XK_q)
		vars->map->rotate += 0.01;
	else if (keysym == XK_e)
		vars->map->rotate -= 0.01;
}

void	handle_tilt(int keysym, t_mlx_vars *vars)
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
		if (vars->map->angle > 1)
		{
			vars->map->angle /= 1.1;
		}
	}
}

int	handle_keypress(int keysym, t_mlx_vars *vars)
{
	int	redraw;

	redraw = 1;
	if (keysym == XK_Escape)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		redraw = 0;
	}
	else if (keysym == XK_w || keysym == XK_s)
		handle_tilt(keysym, vars);
	else if ((keysym >= XK_Left && keysym <= XK_Down) \
			|| keysym == XK_o || keysym == XK_i)
		handle_dir_key(keysym, vars);
	else if ((keysym >= XK_0 && keysym <= XK_9) || keysym == XK_d)
		handle_color_key(keysym, vars);
	else if ((keysym >= XK_q || keysym == XK_e))
		handle_rotate(keysym, vars);
	else if (keysym == XK_n)
		vars->map->z_scale -= (0.001);
	else if (keysym == XK_m)
		vars->map->z_scale += (0.001);
	else if (keysym == XK_comma || keysym == XK_period)
		handle_zoom(keysym, vars);
	else
		redraw = 0;
	ft_printf("Keypress: %d\n", keysym);
	if (redraw)
	{
		project_map(vars->map);
		draw_map(vars->map, vars);
	}
	return (0);
}
