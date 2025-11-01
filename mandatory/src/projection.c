/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 19:40:39 by joao-alm          #+#    #+#             */
/*   Updated: 2025/11/01 19:50:28 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"
#include <math.h>

t_point	proj_point(t_fdf *fdf, int x, int y)
{
	t_point	p;
	float	r[3];

	p = fdf->map[y][x];
	r[0] = x;
	r[1] = y;
	r[2] = p.z * fdf->z_scale;
	p.x = (int)((r[0] - r[1]) * cos(ISO_ANGLE) * fdf->zoom + fdf->x_offset);
	p.y = (int)(((r[0] + r[1]) * sin(ISO_ANGLE) - r[2]) * fdf->zoom
			+ fdf->y_offset);
	return (p);
}
