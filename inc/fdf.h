/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 10:40:19 by joao-alm          #+#    #+#             */
/*   Updated: 2025/10/29 20:18:29 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stddef.h>

# define WIDTH 1600
# define HEIGHT 900
# define STABLE_DELAY_MS 200

# define ISO_ANGLE 0.523599
# define Z_SCALE 0.1

# define ESC_KEY 65307

typedef struct s_rgb
{
	int		r;
	int		g;
	int		b;
}			t_rgb;

typedef struct s_point
{
	int		x;
	int		y;
	int		z;
	int		color;
}			t_point;

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
	int		xproj_min;
	int		xproj_max;
	int		xproj_span;
	int		yproj_min;
	int		yproj_max;
	int		yproj_span;
	int		z_min;
	int		z_max;
	int		z_span;
	int		base_color;
	float	zoom;
	float	x_offset;
	float	y_offset;
}			t_fdf;

// parse
void		parse_map(t_fdf *fdf, char *path);

// prep
void		prep_values(t_fdf *fdf);

// draw
void		draw(t_fdf *fdf);

// util
void		set_pixel(t_img *img, int x, int y, int color);
void		free_map(t_fdf *fdf);
int			ft_exit(t_fdf *fdf);
int			esc_keypress(int key, t_fdf *fdf);

#endif
