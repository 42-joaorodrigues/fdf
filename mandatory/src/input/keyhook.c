/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 20:49:27 by joao-alm          #+#    #+#             */
/*   Updated: 2025/11/01 17:48:18 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"

int	handle_keypress(int key, void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
	if (key == ESC_KEY)
		ft_exit(fdf);
	handle_translation(key, fdf);
	handle_rotation(key, fdf);
	handle_z_scale(key, fdf);
	handle_views(key, fdf);
	draw_fdf(fdf);
	return (0);
}

int	handle_mouse(int button, int x, int y, void *param)
{
	t_fdf	*fdf;
	float	old_zoom;
	float	center_x;
	float	center_y;

	fdf = (t_fdf *)param;
	(void)x;
	(void)y;
	old_zoom = fdf->zoom;
	if (button == 4)
		fdf->zoom *= 1.1;
	else if (button == 5)
	{
		fdf->zoom /= 1.1;
		if (fdf->zoom < 0.1)
			fdf->zoom = 0.1;
	}
	center_x = WIDTH / 2.0f;
	center_y = HEIGHT / 2.0f;
	fdf->x_offset = center_x - (center_x - fdf->x_offset)
		* (fdf->zoom / old_zoom);
	fdf->y_offset = center_y - (center_y - fdf->y_offset)
		* (fdf->zoom / old_zoom);
	draw_fdf(fdf);
	return (0);
}

void	keyhook(t_fdf *fdf)
{
	mlx_hook(fdf->win, 2, 1L << 0, handle_keypress, fdf);
	mlx_hook(fdf->win, 4, 1L << 2, handle_mouse, fdf);
	mlx_hook(fdf->win, 17, 1L << 0, ft_exit, fdf);
}
