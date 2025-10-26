/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 10:40:19 by joao-alm          #+#    #+#             */
/*   Updated: 2025/10/26 14:26:27 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <stddef.h>

# define WIDTH 1600
# define HEIGHT 900
# define STABLE_DELAY_MS 200

# define ESC_KEY 65307

typedef struct s_img
{
	void			*ptr;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
}					t_img;

typedef struct s_point
{
	int				z;
	int				color;
}					t_point;

typedef struct s_map
{
	int				width;
	int				height;
	t_point			**points;
}					t_map;

typedef struct s_fdf
{
	t_map			map;
	void			*mlx;
	void			*win;
	t_img			img;
}					t_fdf;

// parse
void				parse_map(t_map *map, char *path);

// keyhook
void				keyhook(t_fdf *fdf);

// util
size_t				ft_time_ms(void);
void				set_pixel(t_img *img, int x, int y, int color);
unsigned int		get_pixel(t_img *img, int x, int y);
void				free_map(t_map *map);

#endif
