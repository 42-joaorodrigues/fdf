/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 21:13:42 by joao-alm          #+#    #+#             */
/*   Updated: 2025/10/30 15:39:34 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "helper.h"
#include "mlx.h"
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

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
	void	*menu;

	handle_args(ac, av);
	parse_map(&fdf, av[1]);
	prep_values(&fdf);
	fdf.mlx = mlx_init();
	fdf.win = mlx_new_window(fdf.mlx, WIDTH, HEIGHT, "fdf");
	int w = WIDTH;
	int h = HEIGHT;
	menu = mlx_xpm_file_to_image(fdf.mlx, "fdf.xpm", &w, &h);
	mlx_put_image_to_window(fdf.mlx, fdf.win, menu, 0, 0);
	draw(&fdf);
	keyhook(&fdf);
	mlx_loop(fdf.mlx);
	ft_exit(&fdf);
	return (0);
}
