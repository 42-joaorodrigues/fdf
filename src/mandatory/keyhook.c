/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 20:49:27 by joao-alm          #+#    #+#             */
/*   Updated: 2025/11/01 16:01:52 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"

#define ROTATION_STEP 0.1
#define Z_SCALE_STEP 0.1

static void	handle_translation(int key, t_fdf *fdf)
{
	if (key == W_KEY)
		fdf->y_offset += 20;
	else if (key == S_KEY)
		fdf->y_offset -= 20;
	else if (key == A_KEY)
		fdf->x_offset += 20;
	else if (key == D_KEY)
		fdf->x_offset -= 20;
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

static void	set_isometric_view(t_fdf *fdf)
{
	fdf->alpha = 0.0f;
	fdf->theta = 0.0f;
	fdf->gamma = 0.0f;
	fdf->projection_mode = PROJ_ISOMETRIC;
	recalculate_view(fdf);
}

static void	set_frontal_view(t_fdf *fdf)
{
	fdf->alpha = 0.0001f;
	fdf->theta = 0.0f;
	fdf->gamma = 0.0f;
	fdf->projection_mode = PROJ_ORTHOGRAPHIC;
	recalculate_view(fdf);
}

static void	set_top_view(t_fdf *fdf)
{
	fdf->alpha = 1.5708f;
	fdf->theta = 3.14159f;
	fdf->gamma = 3.14159f;
	fdf->projection_mode = PROJ_ORTHOGRAPHIC;
	recalculate_view(fdf);
}

static void	handle_views(int key, t_fdf *fdf)
{
	if (key == I_KEY)
		set_isometric_view(fdf);
	else if (key == F_KEY)
		set_frontal_view(fdf);
	else if (key == T_KEY)
		set_top_view(fdf);
}

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
	draw(fdf);
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
	center_x = WIDTH / 2.0f;
	center_y = HEIGHT / 2.0f;
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
	fdf->x_offset = center_x - (center_x - fdf->x_offset) * (fdf->zoom / old_zoom);
	fdf->y_offset = center_y - (center_y - fdf->y_offset) * (fdf->zoom / old_zoom);
	draw(fdf);
	return (0);
}

void	keyhook(t_fdf *fdf)
{
	mlx_hook(fdf->win, 2, 1L << 0, handle_keypress, fdf);
	mlx_hook(fdf->win, 4, 1L << 2, handle_mouse, fdf);
	mlx_hook(fdf->win, 17, 1L << 0, ft_exit, fdf);
}