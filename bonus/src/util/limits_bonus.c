/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   limits_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 17:06:30 by joao-alm          #+#    #+#             */
/*   Updated: 2025/11/01 19:51:34 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"
#include <limits.h>

t_limit	get_z_limit(t_fdf *fdf)
{
	t_limit	limit_z;
	int		x;
	int		y;
	int		z;

	limit_z.min = INT_MAX;
	limit_z.max = INT_MIN;
	y = -1;
	while (++y < fdf->map_height)
	{
		x = -1;
		while (++x < fdf->map_width)
		{
			z = fdf->map[y][x].z;
			if (z < limit_z.min)
				limit_z.min = z;
			if (z > limit_z.max)
				limit_z.max = z;
		}
	}
	return (limit_z);
}

void	calc_xy_limits(t_fdf *fdf, t_limit *limit_x, t_limit *limit_y)
{
	int		y;
	int		x;
	t_point	proj;

	limit_x->min = INT_MAX;
	limit_x->max = INT_MIN;
	limit_y->min = INT_MAX;
	limit_y->max = INT_MIN;
	y = -1;
	while (++y < fdf->map_height)
	{
		x = -1;
		while (++x < fdf->map_width)
		{
			proj = proj_point(fdf, x, y);
			if (proj.x < limit_x->min)
				limit_x->min = proj.x;
			if (proj.x > limit_x->max)
				limit_x->max = proj.x;
			if (proj.y < limit_y->min)
				limit_y->min = proj.y;
			if (proj.y > limit_y->max)
				limit_y->max = proj.y;
		}
	}
}
