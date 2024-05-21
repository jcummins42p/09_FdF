/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:44:30 by jcummins          #+#    #+#             */
/*   Updated: 2024/05/21 20:54:34 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	map_init(t_map *map)
{
	char			*line;
	char			**spline;

	map->fd = open(map->name, O_RDONLY);
	if (map->fd < 0)
		return (0);
	map->points = malloc(sizeof(t_vector **) * map->height_y);
	if (!map->points)
	{
		close(map->fd);
		return (0);
	}
	else
	{
		line = get_next_line(map->fd);
		spline = ft_split(line, ' ');
		map_assign(map, line, spline);
	}
	close(map->fd);
	return (1);
}

int	set_mlx(t_map *map, t_mlx_vars *mlx)
{
	if (mlx != NULL)
	{
		mlx->mlx = mlx_init();
		if (mlx->mlx != NULL)
		{
			mlx->win = mlx_new_window(mlx->mlx, RES_W, RES_H, map->name);
			if (mlx->win != NULL)
			{
				mlx->map = map;
				mlx_loop_hook(mlx->mlx, &k_no_event, mlx);
				mlx_hook(mlx->win, KeyPress, KeyPressMask, &k_press, mlx);
				mlx_hook(mlx->win, KeyRelease, KeyReleaseMask, &k_release, mlx);
				draw_map(map, mlx);
				return (1);
			}
			mlx_destroy_display(mlx->mlx);
		}
		free(mlx);
	}
	close(map->fd);
	free_map(map);
	return (0);
}

void	cleanup(t_map *map, t_mlx_vars *mlx)
{
	mlx_destroy_display(mlx->mlx);
	free_map(map);
	free(map);
	free(mlx->mlx);
	free(mlx);
}

int	main(int argc, char *argv[])
{
	t_map			*map;
	t_mlx_vars		*mlx;

	if (argc != 2)
	{
		ft_printf("Please provide a map file only\n");
		return (1);
	}
	map = malloc(sizeof (t_map));
	if (!map)
		return (1);
	if (!set_defaults(map, argv) || ! set_dimensions(map))
	{
		ft_printf("Invalid map file\n");
		free(map);
		return (1);
	}
	if (!set_scale(map) || !map_init(map) || !project_map(map))
		return (1);
	mlx = malloc(sizeof(t_mlx_vars));
	if (!set_mlx(map, mlx))
		return (1);
	mlx_loop(mlx->mlx);
	cleanup(map, mlx);
	return (0);
}
