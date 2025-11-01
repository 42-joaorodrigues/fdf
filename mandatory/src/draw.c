/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_fdf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 13:47:12 by joao-alm          #+#    #+#             */
/*   Updated: 2025/11/01 19:27:16 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"

static void	draw_horizontal(t_fdf *fdf, int x, int y, t_point a)
{
	t_point	b;

	if (x != fdf->map_width - 1)
	{
		b = proj_point(fdf, x + 1, y);
		line_draw(&fdf->img, a, b);
	}
}

static void	draw_vertical(t_fdf *fdf, int x, int y, t_point a)
{
	t_point	b;

	if (y != fdf->map_height - 1)
	{
		b = proj_point(fdf, x, y + 1);
		line_draw(&fdf->img, a, b);
	}
}

void	draw_fdf(t_fdf *fdf)
{
	int		y;
	int		x;
	t_point	a;

	fdf->img.ptr = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
	fdf->img.addr = mlx_get_data_addr(fdf->img.ptr, &fdf->img.bits_per_pixel,
			&fdf->img.line_length, &fdf->img.endian);
	y = -1;
	while (++y < fdf->map_height)
	{
		x = -1;
		while (++x < fdf->map_width)
		{
			a = proj_point(fdf, x, y);
			draw_horizontal(fdf, x, y, a);
			draw_vertical(fdf, x, y, a);
		}
	}
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img.ptr, 0, 0);
	mlx_destroy_image(fdf->mlx, fdf->img.ptr);
}
