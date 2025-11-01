/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_key_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 17:30:00 by joao-alm          #+#    #+#             */
/*   Updated: 2025/11/01 19:34:57 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

#define ROTATION_STEP 0.1
#define Z_SCALE_STEP 0.1

void	handle_translation(int key, t_fdf *fdf)
{
	if (key == W_KEY)
		fdf->y_offset += TRANSLATION_FACTOR;
	else if (key == S_KEY)
		fdf->y_offset -= TRANSLATION_FACTOR;
	else if (key == A_KEY)
		fdf->x_offset += TRANSLATION_FACTOR;
	else if (key == D_KEY)
		fdf->x_offset -= TRANSLATION_FACTOR;
}

void	handle_rotation(int key, t_fdf *fdf)
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

void	handle_z_scale(int key, t_fdf *fdf)
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

void	handle_views(int key, t_fdf *fdf)
{
	if (key == I_KEY)
		set_isometric_view(fdf);
	else if (key == F_KEY)
		set_frontal_view(fdf);
	else if (key == T_KEY)
		set_top_view(fdf);
}
