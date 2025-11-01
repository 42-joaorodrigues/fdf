/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 16:30:00 by joao-alm          #+#    #+#             */
/*   Updated: 2025/11/01 19:50:14 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	calculate_view(t_fdf *fdf)
{
	t_limit		limit_x;
	t_limit		limit_y;
	float		zoom_x;
	float		zoom_y;

	fdf->zoom = 1.0f;
	fdf->x_offset = 0.0f;
	fdf->y_offset = 0.0f;
	calc_xy_limits(fdf, &limit_x, &limit_y);
	if (limit_x.min == limit_x.max)
		limit_x.max += 1;
	if (limit_y.min == limit_y.max)
		limit_y.max += 1;
	zoom_x = (float)WIDTH * 0.8f / (float)(limit_x.max - limit_x.min);
	zoom_y = (float)HEIGHT * 0.8f / (float)(limit_y.max - limit_y.min);
	fdf->zoom = zoom_x;
	if (zoom_y < zoom_x)
		fdf->zoom = zoom_y;
	fdf->x_offset = (WIDTH / 2.0f) - ((limit_x.max + limit_x.min) / 2.0f)
		* fdf->zoom;
	fdf->y_offset = (HEIGHT / 2.0f) - ((limit_y.max + limit_y.min) / 2.0f)
		* fdf->zoom;
}
