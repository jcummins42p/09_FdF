/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hookhandlers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:32:48 by jcummins          #+#    #+#             */
/*   Updated: 2024/05/04 12:54:35 by jcummins         ###   ########.fr       */
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

int	handle_keypress(int keysym, t_mlx_vars *vars)
{
	if (keysym == XK_Escape)
		mlx_destroy_window(vars->mlx, vars->win);
	else if (keysym == XK_Left)
		vars->map->offset_x += 10;
	else if (keysym == XK_Right)
		vars->map->offset_x -= 10;
	else if (keysym == XK_Up)
		vars->map->offset_y += 10;
	else if (keysym == XK_Down)
		vars->map->offset_y -= 10;
	else if (keysym == XK_period)
		vars->map->scale += 1;
	else if (keysym == XK_comma)
		vars->map->scale -= 1;
	else if (keysym == XK_n)
		vars->map->z_scale -= 1;
	else if (keysym == XK_m)
		vars->map->z_scale += 1;
	ft_printf("Keypress: %d\n", keysym);
	if (keysym == XK_Left || keysym == XK_Right || keysym == XK_Up || keysym == XK_Down || keysym == XK_period || keysym == XK_comma || keysym == XK_n || keysym == XK_m)
	{
		project_map(vars->map);
		draw_map(vars->map, vars);
	}
	return (0);
}
