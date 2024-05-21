/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 17:27:25 by jcummins          #+#    #+#             */
/*   Updated: 2024/05/21 14:32:31 by jcummins         ###   ########.fr       */
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

typedef struct s_unit_vect
{
	float	x;
	float	y;
	float	z;
}				t_unit_vect;

typedef struct s_vector
{
	int				x;
	int				y;
	float			z;
	int				px;
	int				py;
	unsigned int	c;
	int				c_red;
	int				c_grn;
	int				c_blu;
	float			length;
}				t_vector;

typedef struct s_img_vars
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img_vars;

typedef struct s_map
{
	char			*name;
	int				fd;
	float			rotate;
	float			angle;
	unsigned int	width_x;
	unsigned int	x;
	unsigned int	height_y;
	unsigned int	y;
	unsigned int	scale;
	int				offset_x;
	int				offset_y;
	float			z_scale;
	int				c_default;
	t_vector		***points;
}				t_map;

typedef struct s_mlx_vars
{
	void	*mlx;
	void	*win;
	t_map	*map;
}				t_mlx_vars;

//		hookhandlers.c
int			mlx_close(int keycode, t_mlx_vars *vars);
int			k_no_event(void *vars);
int			k_release(int keysym, void *vars);
int			k_press(int keysym, t_mlx_vars *vars);

//		drawfuncts.c
void		my_mlx_pixel_put(t_img_vars *data, int x, int y, int color);
t_vector	*direction_vector(t_vector *origin, t_vector *end);
void		connect_points(t_img_vars img, t_vector *origin, t_vector *end);
int			project_map(t_map *map);
void		draw_map(t_map *map, t_mlx_vars *mlx);

//		funcs_colour.c
void		colour_components(t_vector *vector);
int			colour_gradient(t_vector *origin, t_vector *end, float ratio);
int			colour_increment(int origin, int increment);
int			get_colour_arg(char *str);
void		set_height_colour(t_map *map, t_vector *point, char *str);

//		vectormath.c
float		vector_length(int x, int y);
float		fl_abs(float f);
float		norm_vd(t_vector *direction, int dimension);
t_unit_vect	*normalize_vector(t_vector *direction);
t_vector	*new_vector(int x, int y, int z, int c);

//		circledraw.c
void		draw_circle(t_img_vars img, t_vector *point, int radius, int color);

//		freehelpers.c
void		free_map(t_map *map);
void		free_split(char **split);

//		init_map.c
int			set_defaults(t_map *map, char **argv);
int			set_scale(t_map *map);
int			set_dimensions(t_map *map);
int			map_assign(t_map *map, char *line, char **spline);
int			map_init(t_map *map);

//		funcs_controls.c
void		k_color_key(int keysym, t_mlx_vars *vars);
void		k_dir_key(int keysym, t_mlx_vars *vars);
void		k_zoom(int keysym, t_mlx_vars *vars);
void		k_rotate(int keysym, t_mlx_vars *vars);
void		k_tilt(int keysym, t_mlx_vars *vars);

//		main.c

#endif
