/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funcs_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 18:16:10 by jcummins          #+#    #+#             */
/*   Updated: 2024/05/20 12:53:08 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_map(t_map *map)
{
	unsigned int	y;
	unsigned int	x;

	y = 0;
	while (y < map->height_y)
	{
		x = 0;
		while (x < map->width_x)
		{
			free(map->points[y][x]);
			x++;
		}
		free(map->points[y++]);
	}
	free(map->points);
}

void	free_split(char **split)
{
	char	**head;

	if (!split)
		return ;
	head = split;
	while (*split)
	{
		free(*split);
		split++;
	}
	free(head);
}
