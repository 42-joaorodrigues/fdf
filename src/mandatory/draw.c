/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 13:47:12 by joao-alm          #+#    #+#             */
/*   Updated: 2025/10/30 17:51:22 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "helper.h"
#include "mlx.h"
#include <math.h>
#include <stdio.h>

t_point proj_point(t_fdf *fdf, int x, int y)
{
    t_point p;
    float   rotated_x, rotated_y, rotated_z;
    float   tmp;
    
    p = fdf->map[y][x];
    
    // Start with the original coordinates
    rotated_x = x;
    rotated_y = y;
    rotated_z = p.z * fdf->z_scale;
    
    // Apply rotations (order matters: typically Z -> Y -> X)
    
    // Rotate around Z axis (gamma)
    tmp = rotated_x;
    rotated_x = tmp * cos(fdf->gamma) - rotated_y * sin(fdf->gamma);
    rotated_y = tmp * sin(fdf->gamma) + rotated_y * cos(fdf->gamma);
    
    // Rotate around Y axis (theta)
    tmp = rotated_x;
    rotated_x = tmp * cos(fdf->theta) + rotated_z * sin(fdf->theta);
    rotated_z = rotated_z * cos(fdf->theta) - tmp * sin(fdf->theta);
    
    // Rotate around X axis (alpha)
    tmp = rotated_y;
    rotated_y = tmp * cos(fdf->alpha) - rotated_z * sin(fdf->alpha);
    rotated_z = tmp * sin(fdf->alpha) + rotated_z * cos(fdf->alpha);
    
    // Now apply isometric projection with rotated coordinates
    p.x = (int)((rotated_x - rotated_y) * cos(ISO_ANGLE) * fdf->zoom + fdf->x_offset);
    p.y = (int)(((rotated_x + rotated_y) * sin(ISO_ANGLE) - rotated_z) * fdf->zoom + fdf->y_offset);
    
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

int is_line_visible(t_point a, t_point b)
{
    // Line is only invisible if both points are off-screen on the SAME side
    if ((a.x < 0 && b.x < 0) || (a.x >= FDF_WIDTH && b.x >= FDF_WIDTH))
        return (0);
    if ((a.y < 0 && b.y < 0) || (a.y >= FDF_HEIGHT && b.y >= FDF_HEIGHT))
        return (0);
    return (1);
}

void	draw(t_fdf *fdf)
{
	int		y;
	int		x;
	t_point	a;
	t_point	b;

	printf("alpha:%f tetha:%f gamma:%f\n", fdf->alpha, fdf->theta, fdf->gamma);
	create_img(fdf);
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
				if (is_line_visible(a, b))
                	new_draw_line(&fdf->img, a, b, 0);
			}
			if (y != fdf->map_height - 1)
			{
				b = proj_point(fdf, x, y + 1);
				if (is_line_visible(a, b))
                	new_draw_line(&fdf->img, a, b, 0);
			}
		}
	}
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img.ptr, 300, 0);
	mlx_destroy_image(fdf->mlx, fdf->img.ptr);
}
