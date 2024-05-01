/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawfuncs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 16:11:00 by jcummins          #+#    #+#             */
/*   Updated: 2024/05/01 20:02:05 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_img_vars *data, int x, int y, int color)
{
	char	*dst;

	if (x > RES_W || x < 0 || y > RES_H || y < 0)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

t_vector	*direction_vector(t_vector *origin, t_vector *end)
{
	t_vector	*direction;

	direction = malloc(sizeof(t_vector));
	if (!direction)
		return (NULL);
	direction->x = end->x - origin->x;
	direction->y = end->y - origin->y;
	direction->dx = norm_vd(direction, direction->x);
	direction->dy = norm_vd(direction, direction->y);
	direction->length = vector_length(direction->x, direction->y);
	return (direction);
}

void	connect_points(t_img_vars img, t_vector *origin, t_vector *end)
{
	t_vector	*dir;
	float		curr_length;
	int			colour;
	int			i;

	dir = direction_vector(origin, end);
	curr_length = 0;
	i = 0;
	while (curr_length <= dir->length)
	{
		colour = colour_gradient(origin->c, end->c, curr_length / dir->length);
		my_mlx_pixel_put(&img, (origin->x + (i * dir->dx)), (origin->y + (i * dir->dy)), (origin->c));
		i++;
		curr_length = vector_length(i * dir->dx, i * dir->dy);
	}
	free (dir);
}

//		calculate the colour at a specific point along a line between 2 pixels
int	colour_gradient(int	c1, int c2, float ratio)
{
	int	r;
	int	g;
	int b;

	r = (c1 >> 16) + ;
	g = c1 >> 8 & 0xFF;
	b = c1 & 0xFF;
	ft_printf("C1 RED: %d, GREEN: %d, BLUE: %d\n", r, g, b);
	r = c2 >> 16;
	g = c2 >> 8 & 0xFF;
	b = c2 & 0xFF;
	ft_printf("C2 RED: %d, GREEN: %d, BLUE: %d\n", r, g, b);
	return (1);
}

