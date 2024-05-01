/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 17:27:25 by jcummins          #+#    #+#             */
/*   Updated: 2024/05/01 19:41:29 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft.h"
# include <mlx.h>
# include <math.h>
# include <X11/keysym.h>
# include <X11/X.h>
//	including X11/keysym so that we can handle key hooks by symbol pressed, not
//	keycode which can change between keyboard layouts.

# define RES_H	600
# define RES_W	800

typedef struct	s_mlx_vars
{
	void	*mlx;
	void	*win;
}				t_mlx_vars;

typedef struct	s_unit_vect
{
	float	x;
	float	y;
	float	z;
}				t_unit_vect;

typedef struct	s_vector
{
	int		x;
	int		y;
	int		z;
	int		c;
	float	length;
	float	dx;
	float	dy;
}				t_vector;

typedef struct	s_img_vars
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img_vars;

typedef struct	s_map
{
	char			*name;
	int				fd;
	unsigned int	width_x;
	unsigned int	height_y;
	unsigned int	scale;
	int				offset;
	t_vector		***points;
}				t_map;

//		mlx
int			mlx_close(int keycode, t_mlx_vars *vars);
int			handle_no_event(void *vars);
int			handle_keyrelease(int keysym, void *vars);
int			handle_keypress(int keysym, t_mlx_vars *vars);

//		drawfuncts.c
void		my_mlx_pixel_put(t_img_vars *data, int x, int y, int color);
void		draw_horizontal_line(t_img_vars img, int y, int x_origin, const int x_end);
void		draw_vertical_line(t_img_vars img, int x, int y_origin, const int y_end);
t_vector	*dir_vector(t_vector *origin, t_vector *end);
void		draw_line(t_img_vars img, t_vector *origin, t_vector *direction);
void		connect_points(t_img_vars img, t_vector *origin, t_vector *end);

//		vectormath.c
float		vector_length(int x, int y);
float		fl_abs(float f);
float		norm_vd(t_vector *direction, int dimension);
t_unit_vect	*normalize_vector(t_vector *direction);
t_vector	*new_vector(int x, int y, int z, int c);

//		circledraw.c
void		draw_circle(t_img_vars img, t_vector *centre, int radius, int color);

//		freehelpers.c
void		free_map(t_map *map);
void		free_split(char **split);


#endif
