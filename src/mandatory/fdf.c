/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 21:13:42 by joao-alm          #+#    #+#             */
/*   Updated: 2025/10/24 14:07:00 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"
#include <stdlib.h>
#include <unistd.h>

void	init(t_fractol *ft)
{
	ft->mlx = mlx_init();
	ft->win = mlx_new_window(ft->mlx, WIDTH, HEIGHT, "fdf");
	ft->img.ptr = mlx_new_image(ft->mlx, WIDTH, HEIGHT);
	ft->img.addr = mlx_get_data_addr(ft->img.ptr, &ft->img.bits_per_pixel,
			&ft->img.line_length, &ft->img.endian);
}

int	main(int ac, char **av)
{
	t_fractol	ft;

	(void)ac;
	(void)av;
	init(&ft);
	keyhook(&ft);
	mlx_loop(ft.mlx);
	mlx_destroy_image(ft.mlx, ft.img.ptr);
	mlx_destroy_window(ft.mlx, ft.win);
	mlx_destroy_display(ft.mlx);
	free(ft.mlx);
	return (0);
}
