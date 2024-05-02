/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funcs_colour.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 16:11:00 by jcummins          #+#    #+#             */
/*   Updated: 2024/05/02 13:13:08 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
