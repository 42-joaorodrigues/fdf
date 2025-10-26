/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 21:13:42 by joao-alm          #+#    #+#             */
/*   Updated: 2025/10/25 20:45:03 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "helper.h"
#include "mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

void	init(t_fdf *fdf)
{
	fdf->mlx = mlx_init();
	fdf->win = mlx_new_window(fdf->mlx, WIDTH, HEIGHT, "fdf");
	fdf->img.ptr = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
	fdf->img.addr = mlx_get_data_addr(fdf->img.ptr, &fdf->img.bits_per_pixel,
			&fdf->img.line_length, &fdf->img.endian);
}

void	handle_args(int ac, char **av)
{
	if (ac != 2)
	{
		ft_putstr_fd("usage: ./fdf <.fdf map file>\n", STDERR_FILENO);
		exit(1);
	}
	if (ft_strlen(av[1]) < 4
		|| ft_strncmp(av[1] + ft_strlen(av[1]) - 4, ".fdf", 4))
	{
		ft_putstr_fd("error: file must end in .fdf\n", STDERR_FILENO);
		exit(1);
	}
}

int	main(int ac, char **av)
{
	t_fdf	fdf;

	handle_args(ac, av);
	parse_map(&fdf.map, av[1]);
	init(&fdf);
	keyhook(&fdf);
	mlx_loop(fdf.mlx);
	mlx_destroy_image(fdf.mlx, fdf.img.ptr);
	mlx_destroy_window(fdf.mlx, fdf.win);
	mlx_destroy_display(fdf.mlx);
	free(fdf.mlx);
	return (0);
}
