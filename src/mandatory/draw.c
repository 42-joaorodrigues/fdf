/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 13:47:12 by joao-alm          #+#    #+#             */
/*   Updated: 2025/10/29 19:25:52 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "helper.h"
#include "mlx.h"
#include <math.h>

t_point	proj_point(t_fdf *fdf, int x, int y)
{
	t_point	p;

	p = fdf->map[y][x];
	p.x = (int)((x - y) * cos(ISO_ANGLE) * fdf->zoom + fdf->x_offset);
	p.y = (int)(((x + y) * sin(ISO_ANGLE) - p.z * Z_SCALE) * fdf->zoom
			+ fdf->y_offset);
	return (p);
}

void	calculate_line_values(t_point a, t_point b, int (*d)[2], int (*step)[2])
{
	(*d)[0] = ft_abs(b.x - a.x);
	(*d)[1] = ft_abs(b.y - a.y);
	if (a.x < b.x)
		(*step)[0] = 1;
	else
		(*step)[0] = -1;
	if (a.y < b.y)
		(*step)[1] = 1;
	else
		(*step)[1] = -1;
}

int	get_color_gradient(t_point pa, t_point pb, int i, int steps)
{
	double	t;
	t_rgb	final;
	t_rgb	a;
	t_rgb	b;

	if (steps == 0)
		t = 0;
	else
		t = (double)i / (double)steps;
	if (t < 0)
		t = 0;
	else if (t > 1)
		t = 1;
	a.r = (pa.color >> 16) & 0xFF;
	a.g = (pa.color >> 8) & 0xFF;
	a.b = pa.color & 0xFF;
	b.r = (pb.color >> 16) & 0xFF;
	b.g = (pb.color >> 8) & 0xFF;
	b.b = pb.color & 0xFF;
	final.r = a.r + (int)((b.r - a.r) * t);
	final.g = a.g + (int)((b.g - a.g) * t);
	final.b = a.b + (int)((b.b - a.b) * t);
	return ((final.r << 16) | (final.g << 8) | final.b);
}

void	new_draw_line(t_img *img, t_point a, t_point b, int i)
{
	int	d[2];
	int	step[2];
	int	err;
	int	e2;

	calculate_line_values(a, b, &d, &step);
	err = d[0] - d[1];
	while (1)
	{
		set_pixel(img, a.x, a.y, get_color_gradient(a, b, i, d[1]));
		if (a.x == b.x && a.y == b.y)
			break ;
		e2 = 2 * err;
		if (e2 > -d[1])
		{
			err -= d[1];
			a.x += step[0];
		}
		if (e2 < d[0])
		{
			err += d[0];
			a.y += step[1];
		}
		i++;
	}
}

void	draw(t_fdf *fdf)
{
	int		y;
	int		x;
	t_point	a;
	t_point	b;

	y = -1;
	while (++y < fdf->map_height)
	{
		x = -1;
		while (++x < fdf->map_width)
		{
			a = proj_point(fdf, x, y);
			if (x != fdf->map_width - 1)
			{
				b = proj_point(fdf, x + 1, y);
				new_draw_line(&fdf->img, a, b, 0);
			}
			if (y != fdf->map_height - 1)
			{
				b = proj_point(fdf, x, y + 1);
				new_draw_line(&fdf->img, a, b, 0);
			}
		}
	}
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img.ptr, 0, 0);
}
