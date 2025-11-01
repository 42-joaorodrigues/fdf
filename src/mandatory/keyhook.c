/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 20:49:27 by joao-alm          #+#    #+#             */
/*   Updated: 2025/11/01 14:10:11 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"

#define ROTATION_STEP 0.1
#define Z_SCALE_STEP 0.1

static void	handle_translation(int key, t_fdf *fdf)
{
	if (key == W_KEY)
		fdf->y_offset -= 20;
	else if (key == S_KEY)
		fdf->y_offset += 20;
	else if (key == A_KEY)
		fdf->x_offset -= 20;
	else if (key == D_KEY)
		fdf->x_offset += 20;
}

static void	handle_rotation(int key, t_fdf *fdf)
{
	if (key == UP_ARROW_KEY)
		fdf->alpha += ROTATION_STEP;
	else if (key == DOWN_ARROW_KEY)
		fdf->alpha -= ROTATION_STEP;
	else if (key == LEFT_ARROW_KEY)
		fdf->theta -= ROTATION_STEP;
	else if (key == RIGHT_ARROW_KEY)
		fdf->theta += ROTATION_STEP;
	else if (key == Q_KEY)
		fdf->gamma -= ROTATION_STEP;
	else if (key == E_KEY)
		fdf->gamma += ROTATION_STEP;
}

static void	handle_z_scale(int key, t_fdf *fdf)
{
	if (key == Z_KEY)
	{
		fdf->z_scale -= Z_SCALE_STEP;
		if (fdf->z_scale < 0.1)
			fdf->z_scale = 0.1;
	}
	else if (key == X_KEY)
		fdf->z_scale += Z_SCALE_STEP;
}

int	handle_keypress(int key, t_fdf *fdf)
{
	if (key == ESC_KEY)
		ft_exit(fdf);
	handle_translation(key, fdf);
	handle_rotation(key, fdf);
	handle_z_scale(key, fdf);
	draw(fdf);
	return (0);
}

int	handle_mouse(int button, int x, int y, t_fdf *fdf)
{
	(void)x;
	(void)y;
	if (button == 4)
	{
		fdf->zoom *= 1.1;
	}
	else if (button == 5)
	{
		fdf->zoom /= 1.1;
		if (fdf->zoom < 0.1)
			fdf->zoom = 0.1;
	}
	draw(fdf);
	return (0);
}

void	keyhook(t_fdf *fdf)
{
	mlx_hook(fdf->win, 2, 1L << 0, handle_keypress, fdf);
	mlx_hook(fdf->win, 4, 1L << 2, handle_mouse, fdf);
	mlx_hook(fdf->win, 17, 1L << 0, ft_exit, fdf);
}