/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 17:27:25 by jcummins          #+#    #+#             */
/*   Updated: 2024/04/26 16:58:00 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft.h"
# include <mlx.h>
# include <math.h>

# define RES_H	600
# define RES_W	800

typedef struct	s_unit_vect
{
	float	x;
	float	y;
	float	z;
}				t_unit_vect;

typedef struct	s_vector
{
	int	x;
	int	y;
	int	z;
	int	c;
}				t_vector;

typedef struct	s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

//		drawfuncts.c
void		my_mlx_pixel_put(t_data *data, int x, int y, int color);
void		draw_horizontal_line(t_data img, int y, int x_origin, const int x_end);
void		draw_vertical_line(t_data img, int x, int y_origin, const int y_end);
void		draw_lline(t_data img, t_vector *origin, t_vector *direction, float length);
void		draw_line(t_data img, t_vector *origin, t_vector *direction);
void		connect_points(t_data img, t_vector *origin, t_vector *end);

//		vectormath.c
float		vector_length(int x, int y);
float		fl_abs(float f);
float		norm_vd(t_vector *direction, int dimension);
t_unit_vect	*normalize_vector(t_vector *direction);
t_vector	*new_vector(int x, int y, int z, int c);

//		circledraw.c
void		draw_circle(t_data img, t_vector *centre, int radius, int color);

#endif
