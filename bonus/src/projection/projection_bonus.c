/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 17:20:00 by joao-alm          #+#    #+#             */
/*   Updated: 2025/11/01 19:34:53 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"
#include <math.h>

void	apply_proj_iso(t_fdf *fdf, t_point *p, float *r)
{
	p->x = (int)((r[0] - r[1]) * cos(ISO_ANGLE) * fdf->zoom + fdf->x_offset);
	p->y = (int)(((r[0] + r[1]) * sin(ISO_ANGLE) - r[2]) * fdf->zoom
			+ fdf->y_offset);
}

void	apply_proj_ortho(t_fdf *fdf, t_point *p, float *r)
{
	p->x = (int)(r[0] * fdf->zoom + fdf->x_offset);
	p->y = (int)(-r[2] * fdf->zoom + fdf->y_offset);
}

void	apply_projection(t_fdf *fdf, t_point *p, float *r)
{
	if (fdf->projection_mode == PROJ_ISOMETRIC)
		apply_proj_iso(fdf, p, r);
	else
		apply_proj_ortho(fdf, p, r);
}

t_point	proj_point(t_fdf *fdf, int x, int y)
{
	t_point	p;
	float	r[3];

	p = fdf->map[y][x];
	r[0] = x;
	r[1] = y;
	r[2] = p.z * fdf->z_scale;
	apply_rotation_z(&r[0], &r[1], fdf->gamma);
	apply_rotation_y(&r[0], &r[2], fdf->theta);
	apply_rotation_x(&r[1], &r[2], fdf->alpha);
	apply_projection(fdf, &p, r);
	return (p);
}
