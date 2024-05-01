/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hookhandlers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:32:48 by jcummins          #+#    #+#             */
/*   Updated: 2024/05/01 17:05:27 by jcummins         ###   ########.fr       */
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
	ft_printf("Keypress: %d\n", keysym);
	return (0);
}
