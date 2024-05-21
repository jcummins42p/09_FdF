/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circledraw.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 16:37:21 by jcummins          #+#    #+#             */
/*   Updated: 2024/05/21 11:49:41 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_circle(t_img_vars img, t_vector *point, int rad, int color)
{
	int	radius_err;
	int	x;
	int	y;

	x = rad;
	y = 0;
	radius_err = 1 - x;
	while (x >= y)
	{
		my_mlx_pixel_put(&img, point->x + x, point->y + y, color);
		my_mlx_pixel_put(&img, point->x - x, point->y + y, color);
		my_mlx_pixel_put(&img, point->x + x, point->y - y, color);
		my_mlx_pixel_put(&img, point->x - x, point->y - y, color);
		my_mlx_pixel_put(&img, point->x + y, point->y + x, color);
		my_mlx_pixel_put(&img, point->x - y, point->y + x, color);
		my_mlx_pixel_put(&img, point->x + y, point->y - x, color);
		my_mlx_pixel_put(&img, point->x - y, point->y - x, color);
		y++;
		if (radius_err < 0)
			radius_err += 2 * y + 1;
		else
			radius_err += 2 * (y - x-- + 1);
	}
}
