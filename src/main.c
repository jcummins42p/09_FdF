/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:44:30 by jcummins          #+#    #+#             */
/*   Updated: 2024/05/20 18:03:39 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	project_map(t_map *map)
{
	double 			rx;
	double 			ry;
	double			cos_theta;
	double			sin_theta;

	map->y = 0;
	cos_theta = cos(map->rotate);
	sin_theta = sin(map->rotate);
	while (map->y < map->height_y)
	{
		map->x = 0;
		while (map->x < map->width_x)
		{
			rx = map->x * cos_theta - map->y * sin_theta;
			ry = map->x * sin_theta	+ map->y * cos_theta;
			map->points[map->y][map->x]->px = (rx - ry) * map->scale + map->offset_x;
			map->points[map->y][map->x]->py = (((rx + ry)) * map->scale / map->angle) + map->offset_y - (int)(map->points[map->y][map->x]->z * (map->z_scale * map->scale));
			map->x++;
		}
		map->y++;
	}
}

int	main(int argc, char *argv[])
{
	t_map			*map;
	t_mlx_vars		*mlx;

	if (argc < 2)
	{
		ft_printf("Please provide a map file\n");
		return (1);
	}
	map = malloc(sizeof (t_map));
	if (!map)
		return (1);
	map->fd = open(argv[1], O_RDONLY);
	if (argc > 2)
		map->z_scale = ft_atoi(argv[2]);
	else
		map->z_scale = 0.1;
	if (argc > 3)
		map->c_default = get_colour_arg(argv[3]);
	else
		map->c_default = 0x00FFFFFF;
	if (map->fd < 0)
	{
		free (map);
		return (1);
	}
	map->name = (argv[1]);
	if (!set_dimensions(map))
	{
		ft_printf("Invalid map file\n");
		free(map);
		return (1);
	}
	set_scale(map);
	map->angle = 2.0;
	map->rotate = 0;
	map_init(map);
	project_map(map);
	mlx = malloc(sizeof(t_mlx_vars));
	if (mlx == NULL)
	{
		close(map->fd);
		free_map(map);
		return (1);
	}
	mlx->mlx = mlx_init();
	if (mlx->mlx == NULL)
	{
		free(mlx);
		close(map->fd);
		free_map(map);
		return (1);
	}
	mlx->win = mlx_new_window(mlx->mlx, RES_W, RES_H, map->name);
	if (mlx->win == NULL)
	{
		mlx_destroy_display(mlx->mlx);
		free(mlx);
		close(map->fd);
		free_map(map);
		return (1);
	}
	mlx->map = map;
	mlx_loop_hook(mlx->mlx, &handle_no_event, mlx);
	mlx_hook(mlx->win, KeyPress, KeyPressMask, &handle_keypress, mlx);
	mlx_hook(mlx->win, KeyRelease, KeyReleaseMask, &handle_keyrelease, mlx);
	ft_printf("%s: %d x %d\n", map->name, map->height_y, map->width_x);
	draw_map(map, mlx);
	mlx_loop(mlx->mlx);
	mlx_destroy_display(mlx->mlx);
	free_map(map);
	free(map);
	free(mlx->mlx);
	free(mlx);
	return (0);
}
