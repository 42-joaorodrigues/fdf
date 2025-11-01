/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 10:40:19 by joao-alm          #+#    #+#             */
/*   Updated: 2025/11/01 16:01:52 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stddef.h>

# define WIDTH 1600
# define HEIGHT 900
# define TRANSLATION_FACTOR 100
# define ZOOM_FACTOR 1.5

# define ISO_ANGLE 0.523599
# define Z_SCALE 1

# define PROJ_ISOMETRIC 0
# define PROJ_ORTHOGRAPHIC 1

# define ESC_KEY 65307
# define W_KEY 119
# define S_KEY 115
# define A_KEY 97
# define D_KEY 100
# define Q_KEY 113
# define E_KEY 101
# define Z_KEY 122
# define X_KEY 120
# define UP_ARROW_KEY 65362
# define DOWN_ARROW_KEY 65364
# define LEFT_ARROW_KEY 65361
# define RIGHT_ARROW_KEY 65363
# define I_KEY 105
# define T_KEY 116
# define F_KEY 102

typedef struct s_rgb
{
	int			r;
	int			g;
	int			b;
}				t_rgb;

typedef struct s_point
{
	int			x;
	int			y;
	int			z;
	int			color;
}				t_point;

typedef struct s_img
{
	void		*ptr;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_img;

typedef struct s_fdf
{
	void		*mlx;
	void		*win;
	t_img		img;
	t_point		**map;
	int			map_width;
	int			map_height;
	int			xproj_min;
	int			xproj_max;
	int			xproj_span;
	int			yproj_min;
	int			yproj_max;
	int			yproj_span;
	int			z_min;
	int			z_max;
	int			z_span;
	int			base_color;
	float		zoom;
	float		x_offset;
	float		y_offset;
	float		z_scale;
	float		alpha;
	float		theta;
	float		gamma;
	int			projection_mode;
}				t_fdf;

// parse
void			parse_map(t_fdf *fdf, char *path);

// prep
void			prep_values(t_fdf *fdf);
void			recalculate_view(t_fdf *fdf);

// draw
void			draw(t_fdf *fdf);
t_point			proj_point(t_fdf *fdf, int x, int y);

// keyhook
void			keyhook(t_fdf *fdf);

// util
void			set_pixel(t_img *img, int x, int y, int color);
void			create_img(t_fdf *fdf);
void			free_map(t_fdf *fdf);
int				ft_exit(void *param);

#endif
