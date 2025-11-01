/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 21:13:42 by joao-alm          #+#    #+#             */
/*   Updated: 2025/11/01 19:34:28 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"
#include "libft.h"
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

	handle_args(ac, av);
	parse_map(&fdf, av[1]);
	assign_colors(&fdf);
	fdf.z_scale = 1;
	set_isometric_view(&fdf);
	fdf.mlx = mlx_init();
	fdf.win = mlx_new_window(fdf.mlx, WIDTH, HEIGHT, "fdf");
	draw_fdf(&fdf);
	keyhook(&fdf);
	mlx_loop(fdf.mlx);
	ft_exit(&fdf);
	return (0);
}
