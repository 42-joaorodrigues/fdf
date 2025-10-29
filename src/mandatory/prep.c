/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 17:28:15 by joao-alm          #+#    #+#             */
/*   Updated: 2025/10/29 19:39:00 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "helper.h"
#include <limits.h>
#include <math.h>

void	get_z_limits(t_fdf *fdf)
{
	int	x;
	int	y;
	int	z;

	y = -1;
	while (++y < fdf->map_height)
	{
		x = -1;
		while (++x < fdf->map_width)
		{
			z = fdf->map[y][x].z;
			if (z < fdf->z_min)
				fdf->z_min = z;
			if (z > fdf->z_max)
				fdf->z_max = z;
		}
	}
	fdf->z_span = fdf->z_max - fdf->z_min;
}

void	get_proj_limits(t_fdf *fdf)
{
	int		y;
	int		x;
	int		z;
	float	xproj;
	float	yproj;

	y = -1;
	while (++y < fdf->map_height)
	{
		x = -1;
		while (++x < fdf->map_width)
		{
			z = fdf->map[y][x].z;
			xproj = (x - y) * cos(ISO_ANGLE);
			yproj = (x + y) * sin(ISO_ANGLE) - z * Z_SCALE;
			if (xproj < fdf->xproj_min)
				fdf->xproj_min = (int)xproj;
			else if (xproj > fdf->xproj_max)
				fdf->xproj_max = (int)xproj;
			if (yproj < fdf->yproj_min)
				fdf->yproj_min = (int)yproj;
			else if (yproj > fdf->yproj_max)
				fdf->yproj_max = (int)yproj;
		}
	}
}

int	get_shade(int base_color, float ratio)
{
	int	r;
	int	g;
	int	b;

	r = (base_color >> 16) & 0xFF;
	g = (base_color >> 8) & 0xFF;
	b = base_color & 0xFF;
	r = r + (int)((255 - r) * ratio);
	g = g + (int)((255 - g) * ratio);
	b = b + (int)((255 - b) * ratio);
	return ((r << 16) | (g << 8) | b);
}

void	assign_colors(t_fdf *fdf)
{
	int		x;
	int		y;
	t_point	*point;
	float	ratio;

	y = -1;
	while (++y < fdf->map_height)
	{
		x = -1;
		while (++x < fdf->map_width)
		{
			point = &fdf->map[y][x];
			if (point->color == -1)
			{
				ratio = (float)(point->z - fdf->z_min) / fdf->z_span;
				point->color = get_shade(fdf->base_color, ratio);
			}
		}
	}
}

void	prep_values(t_fdf *fdf)
{
	float	zoom_x;
	float	zoom_y;

	fdf->z_min = INT_MAX;
	fdf->z_max = INT_MIN;
	get_z_limits(fdf);
	fdf->z_span = ft_abs(fdf->z_max - fdf->z_min);
	fdf->xproj_min = INT_MAX;
	fdf->xproj_max = INT_MIN;
	fdf->yproj_min = INT_MAX;
	fdf->yproj_max = INT_MIN;
	get_proj_limits(fdf);
	fdf->xproj_span = ft_abs(fdf->xproj_max - fdf->xproj_min);
	fdf->yproj_span = ft_abs(fdf->yproj_max - fdf->yproj_min);
	fdf->base_color = 0xFF0000;
	assign_colors(fdf);
	zoom_y = (float)HEIGHT * 0.8f / (float)fdf->yproj_span;
	zoom_x = (float)WIDTH * 0.8f / (float)fdf->xproj_span;
	fdf->zoom = zoom_x;
	if (zoom_y < zoom_x)
		fdf->zoom = zoom_y;
	fdf->x_offset = (WIDTH / 2.0f) - ((fdf->xproj_max + fdf->xproj_min) / 2.0f)
		* fdf->zoom;
	fdf->y_offset = (HEIGHT / 2.0f) - ((fdf->yproj_max + fdf->yproj_min) / 2.0f)
		* fdf->zoom;
}
