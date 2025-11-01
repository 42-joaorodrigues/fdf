/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 17:10:00 by joao-alm          #+#    #+#             */
/*   Updated: 2025/11/01 17:42:53 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
	t_limit	z_limit;

	z_limit = get_z_limit(fdf);
	y = -1;
	while (++y < fdf->map_height)
	{
		x = -1;
		while (++x < fdf->map_width)
		{
			point = &fdf->map[y][x];
			if (point->color == -1)
			{
				ratio = (float)(point->z - z_limit.min) / (z_limit.max
						- z_limit.min);
				point->color = get_shade(COLOR, ratio);
			}
		}
	}
}
