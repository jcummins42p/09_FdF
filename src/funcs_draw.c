/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funcs_draw.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 16:11:00 by jcummins          #+#    #+#             */
/*   Updated: 2024/05/02 13:17:39 by jcummins         ###   ########.fr       */
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
