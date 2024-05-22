/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:44:30 by jcummins          #+#    #+#             */
/*   Updated: 2024/05/22 17:54:57 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	cleanup(t_mlx_vars *mlx)
{
	mlx_destroy_display(mlx->mlx);
	free_map(mlx->map);
	free(mlx->map);
	free(mlx->mlx);
	free(mlx);
}

int	handle_destroy(void *params)
{
	t_mlx_vars	*vars;

	vars = (t_mlx_vars *)params;
	k_press(0xff1b, vars);
	return (0);
}

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
				mlx_hook(mlx->win, KeyPress, KeyPressMask, &k_press, mlx);
				mlx_hook(mlx->win, KeyRelease, KeyReleaseMask, &k_release, mlx);
				mlx_hook(mlx->win, ButtonPress, ButtonPressMask, &b_press, mlx);
				mlx_hook(mlx->win, ButtonRelease, ButtonReleaseMask, \
						&b_release, mlx);
				mlx_hook(mlx->win, ON_DESTROY, ButtonPressMask, \
						&handle_destroy, mlx);
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

int	main(int argc, char *argv[])
{
	t_map			*map;
	t_mlx_vars		*mlx;

	map = malloc(sizeof (t_map));
	if (!map)
		return (1);
	if (argc != 2 || !set_defaults(map, argv) || ! set_dimensions(map))
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
	draw_map(map, mlx);
	display_hud(mlx);
	mlx_loop(mlx->mlx);
	mlx_destroy_window(mlx->mlx, mlx->win);
	cleanup(mlx);
	return (0);
}
