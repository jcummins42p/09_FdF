/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectormaths.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 16:05:20 by jcummins          #+#    #+#             */
/*   Updated: 2024/04/30 18:18:05 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

float	vector_length(int x, int y)
{
	return (sqrtf((x * x) + (y * y)));
}

float	fl_abs(float f)
{
	if (f < 0)
		f = -f;
	return (f);
}

float	norm_vd(t_vector *direction, int dimension)
{
	float	v_len;

	v_len = vector_length(direction->x, direction->y);
	if(v_len != 0)
		return (dimension / v_len);
	else
		return (0);
}

t_unit_vect	*normalize_vector(t_vector *direction)
{
	t_unit_vect	*output;
	float		v_len;

	output = malloc(sizeof(t_unit_vect));
	if (!output)
		return (NULL);
	v_len = vector_length(direction->x, direction->y);
	if (v_len != 0)
	{
		output->x = direction->x / v_len;
		output->y = direction->y / v_len;
		output->z = direction->z / v_len;
	}
	return (output);
}

t_vector	*new_vector(int x, int y, int z, int c)
{
	t_vector	*output;

	output = malloc(sizeof(t_vector));
	if (!output)
		return (NULL);
	output->x = x;
	output->y = y;
	output->z = z;
	output->c = c;
	return (output);
}
