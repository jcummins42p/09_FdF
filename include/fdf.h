/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 17:27:25 by jcummins          #+#    #+#             */
/*   Updated: 2024/05/03 17:57:00 by jcummins         ###   ########.fr       */
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

# define RES_H	900
# define RES_W	1800

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
	int		px;
	int		py;
	unsigned int		c;
	int		c_red;
	int		c_grn;
	int		c_blu;
	float	length;
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
	unsigned int	offset_x;
	unsigned int	offset_y;
	int				z_scale;
	int				c_default;
	t_vector		***points;
}				t_map;

typedef struct	s_mlx_vars
{
	void	*mlx;
	void	*win;
	t_map	*map;
}				t_mlx_vars;

//		mlx
int			mlx_close(int keycode, t_mlx_vars *vars);
int			handle_no_event(void *vars);
int			handle_keyrelease(int keysym, void *vars);
int			handle_keypress(int keysym, t_mlx_vars *vars);

//		drawfuncts.c
void		my_mlx_pixel_put(t_img_vars *data, int x, int y, int color);
t_vector	*direction_vector(t_vector *origin, t_vector *end);
void		connect_points(t_img_vars img, t_vector *origin, t_vector *end);

//		funcs_colour.c
void		colour_components(t_vector *vector);
int			colour_gradient(t_vector *origin, t_vector *end, float ratio);
int			colour_increment(int origin, int increment);
int			get_colour_arg(char *str);

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

//		main.c
int			draw_map(t_map *map, t_mlx_vars *mlx);

#endif
