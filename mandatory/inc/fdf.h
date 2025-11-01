/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 10:40:19 by joao-alm          #+#    #+#             */
/*   Updated: 2025/11/01 18:25:10 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stddef.h>
# include "mlx_helper.h"
# include "types.h"

# define WIDTH 1600
# define HEIGHT 900
# define COLOR 0x306468
# define TRANSLATION_FACTOR 100
# define ZOOM_FACTOR 1.5

# define ISO_ANGLE 0.523599

# define PROJ_ISOMETRIC 0
# define PROJ_ORTHOGRAPHIC 1

typedef struct s_fdf
{
	void	*mlx;
	void	*win;
	t_img	img;
	t_point	**map;
	int		map_width;
	int		map_height;
	float	zoom;
	float	x_offset;
	float	y_offset;
	float	z_scale;
	float	alpha;
	float	theta;
	float	gamma;
	int		projection_mode;
}			t_fdf;

// limits
t_limit		get_z_limit(t_fdf *fdf);
void		calc_xy_limits(t_fdf *fdf, t_limit *limit_x, t_limit *limit_y);

// parse
void		parse_map(t_fdf *fdf, char *path);

// prep
void		prep_values(t_fdf *fdf);
void		calculate_view(t_fdf *fdf);

// color
int			get_shade(int base_color, float ratio);
void		assign_colors(t_fdf *fdf);

// draw
void		draw_fdf(t_fdf *fdf);

// projection
void		apply_proj_iso(t_fdf *fdf, t_point *p, float *r);
void		apply_proj_ortho(t_fdf *fdf, t_point *p, float *r);
void		apply_projection(t_fdf *fdf, t_point *p, float *r);
t_point		proj_point(t_fdf *fdf, int x, int y);

// line
void		line_draw(t_img *img, t_point a, t_point b);
int			is_line_visible(t_point a, t_point b);

// bresenham
void		init_bresenham_deltas(t_point a, t_point b, int *delta);
void		init_bresenham_steps(t_point a, t_point b, int *step);
void		bresenham_step_x(int *err, int *x, int delta_y, int step_x);
void		bresenham_step_y(int *err, int *y, int delta_x, int step_y);

// color_gradient
t_rgb		extract_rgb(int color);
double		calculate_interpolation(int current_step, int total_steps);
int			get_color_gradient(t_point start, t_point end, int step, int total);

// rotation
void		apply_rotation_z(float *rotated_x, float *rotated_y, float gamma);
void		apply_rotation_y(float *rotated_x, float *rotated_z, float theta);
void		apply_rotation_x(float *rotated_y, float *rotated_z, float alpha);

// keyhook
void		handle_translation(int key, t_fdf *fdf);
void		handle_rotation(int key, t_fdf *fdf);
void		handle_z_scale(int key, t_fdf *fdf);
void		keyhook(t_fdf *fdf);

// views
void		set_isometric_view(t_fdf *fdf);
void		set_frontal_view(t_fdf *fdf);
void		set_top_view(t_fdf *fdf);
void		handle_views(int key, t_fdf *fdf);

// util
void		set_pixel(t_img *img, int x, int y, int color);
void		free_map(t_fdf *fdf);
int			ft_exit(void *param);

#endif
