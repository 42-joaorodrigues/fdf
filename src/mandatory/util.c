/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 13:46:34 by joao-alm          #+#    #+#             */
/*   Updated: 2025/10/29 16:26:09 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"
#include <stdlib.h>
#include <sys/time.h>

void	set_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	free_map(t_fdf *fdf)
{
	int	i;

	i = -1;
	while (++i < fdf->map_height)
		free(fdf->map[i]);
	free(fdf->map);
}

int	ft_exit(t_fdf *fdf)
{
	mlx_destroy_image(fdf->mlx, fdf->img.ptr);
	mlx_destroy_window(fdf->mlx, fdf->win);
	mlx_destroy_display(fdf->mlx);
	free(fdf->mlx);
	free_map(fdf);
	exit(0);
	return (0);
}

int	esc_keypress(int key, t_fdf *fdf)
{
	if (key == ESC_KEY)
		ft_exit(fdf);
	return (0);
}
