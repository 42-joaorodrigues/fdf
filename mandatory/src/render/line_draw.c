/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_draw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 16:40:00 by joao-alm          #+#    #+#             */
/*   Updated: 2025/11/01 18:56:26 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"

static void	draw_low_slope(t_img *img, t_point start, t_point end,
		t_bresenham *bres)
{
	int	i;
	int	color;

	i = 0;
	color = get_color_gradient(start, end, i, bres->dx);
	set_pixel(img, start.x, start.y, color);
	while (i < bres->dx)
	{
		start.x += bres->step_x;
		if (bres->p < 0)
			bres->p = bres->p + 2 * bres->dy;
		else
		{
			start.y += bres->step_y;
			bres->p = bres->p + 2 * bres->dy - 2 * bres->dx;
		}
		i++;
		color = get_color_gradient(start, end, i, bres->dx);
		set_pixel(img, start.x, start.y, color);
	}
}

static void	draw_high_slope(t_img *img, t_point start, t_point end,
		t_bresenham *bres)
{
	int	i;
	int	color;

	i = 0;
	color = get_color_gradient(start, end, i, bres->dy);
	set_pixel(img, start.x, start.y, color);
	while (i < bres->dy)
	{
		start.y += bres->step_y;
		if (bres->p < 0)
			bres->p = bres->p + 2 * bres->dx;
		else
		{
			start.x += bres->step_x;
			bres->p = bres->p + 2 * bres->dx - 2 * bres->dy;
		}
		i++;
		color = get_color_gradient(start, end, i, bres->dy);
		set_pixel(img, start.x, start.y, color);
	}
}

static void	init_bresenham(t_point start, t_point end, t_bresenham *bres)
{
	bres->dx = ft_abs(end.x - start.x);
	bres->dy = ft_abs(end.y - start.y);
	if (start.x < end.x)
		bres->step_x = 1;
	else
		bres->step_x = -1;
	if (start.y < end.y)
		bres->step_y = 1;
	else
		bres->step_y = -1;
	if (bres->dx >= bres->dy)
		bres->p = 2 * bres->dy - bres->dx;
	else
		bres->p = 2 * bres->dx - bres->dy;
}

void	line_draw(t_img *img, t_point start, t_point end)
{
	t_bresenham	bres;

	init_bresenham(start, end, &bres);
	if (bres.dx >= bres.dy)
		draw_low_slope(img, start, end, &bres);
	else
		draw_high_slope(img, start, end, &bres);
}
