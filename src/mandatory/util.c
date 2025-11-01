/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 13:46:34 by joao-alm          #+#    #+#             */
/*   Updated: 2025/10/30 15:38:53 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"
#include <stdlib.h>
#include <sys/time.h>

void	set_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= FDF_WIDTH || y < 0 || y >= FDF_HEIGHT)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	create_img(t_fdf *fdf)
{
	fdf->img.ptr = mlx_new_image(fdf->mlx, FDF_WIDTH, FDF_HEIGHT);
	fdf->img.addr = mlx_get_data_addr(fdf->img.ptr, &fdf->img.bits_per_pixel,
			&fdf->img.line_length, &fdf->img.endian);
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
	mlx_destroy_window(fdf->mlx, fdf->win);
	mlx_destroy_display(fdf->mlx);
	free(fdf->mlx);
	free_map(fdf);
	exit(0);
	return (0);
}
