/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 10:25:16 by joao-alm          #+#    #+#             */
/*   Updated: 2025/10/25 16:47:26 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"
#include <stdlib.h>

static int	close_window(t_fdf *fdf)
{
	mlx_destroy_image(fdf->mlx, fdf->img.ptr);
	mlx_destroy_window(fdf->mlx, fdf->win);
	mlx_destroy_display(fdf->mlx);
	free(fdf->mlx);
	exit(0);
	return (0);
}

static int	esc_keypress(int key, t_fdf *fdf)
{
	if (key == ESC_KEY)
		close_window(fdf);
	return (0);
}

void	keyhook(t_fdf *fdf)
{
	mlx_hook(fdf->win, 17, 1L << 0, close_window, fdf);
	mlx_hook(fdf->win, 2, 1L << 0, esc_keypress, fdf);
}
