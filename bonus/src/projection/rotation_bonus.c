/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 16:35:00 by joao-alm          #+#    #+#             */
/*   Updated: 2025/11/01 19:34:51 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"
#include <math.h>

void	apply_rotation_z(float *rotated_x, float *rotated_y, float gamma)
{
	float	tmp;

	tmp = *rotated_x;
	*rotated_x = tmp * cos(gamma) - *rotated_y * sin(gamma);
	*rotated_y = tmp * sin(gamma) + *rotated_y * cos(gamma);
}

void	apply_rotation_y(float *rotated_x, float *rotated_z, float theta)
{
	float	tmp;

	tmp = *rotated_x;
	*rotated_x = tmp * cos(theta) + *rotated_z * sin(theta);
	*rotated_z = *rotated_z * cos(theta) - tmp * sin(theta);
}

void	apply_rotation_x(float *rotated_y, float *rotated_z, float alpha)
{
	float	tmp;

	tmp = *rotated_y;
	*rotated_y = tmp * cos(alpha) - *rotated_z * sin(alpha);
	*rotated_z = tmp * sin(alpha) + *rotated_z * cos(alpha);
}
