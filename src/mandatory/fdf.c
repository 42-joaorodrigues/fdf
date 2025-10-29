/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 21:13:42 by joao-alm          #+#    #+#             */
/*   Updated: 2025/10/29 19:36:43 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "helper.h"
#include "mlx.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

void	init_mlx(t_fdf *fdf)
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
	if (ft_strlen(av[1]) < 4 || ft_strcmp(av[1] + ft_strlen(av[1]) - 4, ".fdf"))
	{
		ft_putstr_fd("error: file must be of type .fdf\n", STDERR_FILENO);
		exit(1);
	}
}

int	main(int ac, char **av)
{
	t_fdf	fdf;

	handle_args(ac, av);
	parse_map(&fdf, av[1]);
	prep_values(&fdf);
	init_mlx(&fdf);
	draw(&fdf);
	mlx_hook(fdf.win, 17, 1L << 0, ft_exit, &fdf);
	mlx_hook(fdf.win, 2, 1L << 0, esc_keypress, &fdf);
	mlx_loop(fdf.mlx);
	ft_exit(&fdf);
	return (0);
}
