/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawfuncs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 16:11:00 by jcummins          #+#    #+#             */
/*   Updated: 2024/05/01 21:26:52 by jcummins         ###   ########.fr       */
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
	direction->length = vector_length(direction->x, direction->y);
	return (direction);
}

void	connect_points(t_img_vars img, t_vector *origin, t_vector *end)
{
	t_vector	*dir;
	int			colour;
	float		step;
	float		i;

	dir = direction_vector(origin, end);
	step = 1.0 / dir->length;
	i = 0.0;
	while (i <= 1.0)
	{
		colour_components(origin);
		colour_components(end);
		colour = colour_gradient(origin, end, i);
		my_mlx_pixel_put(&img, (origin->x + (i * dir->x)), \
				(origin->y + (i * dir->y)), colour);
		i += step;
	}
	free (dir);
}

void	colour_components(t_vector *vector)
{
	vector->c_red = vector->c >> 16;
	vector->c_grn = vector->c >> 8 & 0xFF;
	vector->c_blu = vector->c & 0xFF;
}

int	colour_gradient(t_vector *origin, t_vector *end, float ratio)
{
	int	red;
	int	grn;
	int	blu;
	int	out;

	red = fmin(fmax(0, (int)origin->c_red + \
				(end->c_red - origin->c_red) * ratio), 255);
	grn = fmin(fmax(0, (int)origin->c_grn + \
				(end->c_grn - origin->c_grn) * ratio), 255);
	blu = fmin(fmax(0, (int)origin->c_blu + \
				(end->c_blu - origin->c_blu) * ratio), 255);
	out = (red << 16) | (grn << 8) | blu;
	return (out);
}
