/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   limits.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 19:39:54 by joao-alm          #+#    #+#             */
/*   Updated: 2025/11/01 19:50:21 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"
#include <limits.h>

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
