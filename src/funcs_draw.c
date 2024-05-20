/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funcs_draw.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 16:11:00 by jcummins          #+#    #+#             */
/*   Updated: 2024/05/20 13:38:10 by jcummins         ###   ########.fr       */
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
	direction->x = end->px - origin->px;
	direction->y = end->py - origin->py;
	direction->length = vector_length(direction->x, direction->y);
	return (direction);
}

void	connect_points(t_img_vars img, t_vector *origin, t_vector *end)
{
	t_vector	*dir;
	int			colour;
	float		step;
	float		i;

	if ((origin->px <= RES_W + 50 && origin->py <= RES_H + 50) || (end->px <= RES_W + 50 && end->py <= RES_H + 50))
	{
		dir = direction_vector(origin, end);
		step = 1.0 / dir->length;
		i = 0.0;
		while (i <= 1.0)
		{
			colour_components(origin);
			colour_components(end);
			colour = colour_gradient(origin, end, i);
			my_mlx_pixel_put(&img, (origin->px + (i * dir->x)), \
					(origin->py + (i * dir->y)), colour);
			i += step;
		}
		free (dir);
	}
}

int	draw_map(t_map *map, t_mlx_vars *mlx)
{
	t_img_vars		img;
	unsigned int	x;
	unsigned int	y;

	img.img = mlx_new_image(mlx->mlx, RES_W, RES_H);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	y = 0;
	while (y < map->height_y - 1)
	{
		x = 0;
		while (x < map->width_x - 1)
		{
			connect_points(img, map->points[y][x], map->points[y][x + 1]);
			connect_points(img, map->points[y][x], map->points[y + 1][x]);
			x++;
		}
		connect_points(img, map->points[y][x], map->points[y + 1][x]);
		y++;
	}
	x = 0;
	while (x < map->width_x - 1)
	{
		connect_points(img, map->points[y][x], map->points[y][x + 1]);
		x++;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->win, img.img, 0, 0);
	mlx_destroy_image(mlx->mlx, img.img);
	return (1);
}
