/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawfuncs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 16:11:00 by jcummins          #+#    #+#             */
/*   Updated: 2024/04/30 23:05:01 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x > RES_W || x < 0 || y > RES_H || y < 0)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

//		draw horizontal line at set y row between two x values
void	draw_horizontal_line(t_data img, int y, int x_origin, const int x_end)
{
	if (x_origin < x_end)
	{
		while (x_origin < x_end)
			my_mlx_pixel_put(&img, x_origin++, y, 0x00FF0000);
	}
	else
	{
		while (x_origin > x_end)
			my_mlx_pixel_put(&img, x_origin--, y, 0x00FF0000);
	}
}

//		draw vertical line at set x column between two y values
void	draw_vertical_line(t_data img, int x, int y_origin, const int y_end)
{
	if (y_origin < y_end)
	{
		while (y_origin < y_end)
			my_mlx_pixel_put(&img, x, y_origin++, 0x00FF0000);
	}
	else
	{
		while (y_origin > y_end)
			my_mlx_pixel_put(&img, x, y_origin--, 0x00FF0000);
	}
}

//		draw a direction vector from a position vector for set length
void	draw_lline(t_data img, t_vector *origin, t_vector *direction, float length, float dc)
{
	float	dx = norm_vd(direction, direction->x);
	float	dy = norm_vd(direction, direction->y);
	float	curr_length;
	int		i;

	i = 0;
	curr_length = 0;
	while (curr_length <= length)
	{
		my_mlx_pixel_put(&img, (origin->x + (i * dx)), (origin->y + (i * dy)), (origin->c + (i * dc)));
		i++;
		curr_length = vector_length(i * dx, i * dy);
	}
}

//		draw a direction vector from a position for correct length of direction vector
void	draw_line(t_data img, t_vector *origin, t_vector *direction)
{
	float	dx = norm_vd(direction, direction->x);
	float	dy = norm_vd(direction, direction->y);
	int	i;

	i = 0;
	while (i * dy <= direction->y)
	{
		my_mlx_pixel_put(&img, (origin->x + (i * dx)), (origin->y + (i * dy)), origin->c);
		i++;
	}
}

//		draw a line between two position vectors
void	connect_points(t_data img, t_vector *origin, t_vector *end)
{
	t_vector	*direction;
	float		length;
	float		colour;

	direction = malloc(sizeof(t_vector));
	if (!direction)
		return ;
	direction->x = end->x - origin->x;
	direction->y = end->y - origin->y;
	length = vector_length(direction->x, direction->y);
	colour = (end->c - origin->c) / length;
	draw_lline(img, origin, direction, length, colour);
	free (direction);
}
