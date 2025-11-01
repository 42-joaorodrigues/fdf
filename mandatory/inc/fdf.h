/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 10:40:19 by joao-alm          #+#    #+#             */
/*   Updated: 2025/11/01 19:41:59 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "types.h"
# include <stddef.h>

# define WIDTH 1600
# define HEIGHT 900
# define COLOR 0x306468

# define ISO_ANGLE 0.523599

# define ESC_KEY 65307

typedef struct s_img
{
	void	*ptr;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_img;

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

// draw
void		draw_fdf(t_fdf *fdf);

// limits
void		calc_xy_limits(t_fdf *fdf, t_limit *limit_x, t_limit *limit_y);

// line_draw
void		line_draw(t_img *img, t_point a, t_point b);

// parse
void		parse_map(t_fdf *fdf, char *path);

// projection
t_point		proj_point(t_fdf *fdf, int x, int y);

// view
void		calculate_view(t_fdf *fdf);

// util
void		set_pixel(t_img *img, int x, int y, int color);
int			handle_keypress(int key, void *param);
void		free_map(t_fdf *fdf);
int			ft_exit(void *param);

#endif
