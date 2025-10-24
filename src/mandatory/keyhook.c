/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 10:25:16 by joao-alm          #+#    #+#             */
/*   Updated: 2025/10/24 14:07:46 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"
#include <stdlib.h>

static int	close_window(t_fractol *ft)
{
	mlx_destroy_image(ft->mlx, ft->img.ptr);
	mlx_destroy_window(ft->mlx, ft->win);
	mlx_destroy_display(ft->mlx);
	free(ft->mlx);
	exit(0);
	return (0);
}

static int	esc_keypress(int key, t_fractol *ft)
{
	if (key == ESC_KEY)
		close_window(ft);
	return (0);
}

void	keyhook(t_fractol *ft)
{
	mlx_hook(ft->win, 17, 1L << 0, close_window, ft);
	mlx_hook(ft->win, 2, 1L << 0, esc_keypress, ft);
}
