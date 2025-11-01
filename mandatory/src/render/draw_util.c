/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 17:49:35 by joao-alm          #+#    #+#             */
/*   Updated: 2025/11/01 17:49:58 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	set_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	is_line_visible(t_point a, t_point b)
{
	if ((a.x < 0 && b.x < 0) || (a.x >= WIDTH && b.x >= WIDTH))
		return (0);
	if ((a.y < 0 && b.y < 0) || (a.y >= HEIGHT && b.y >= HEIGHT))
		return (0);
	return (1);
}
