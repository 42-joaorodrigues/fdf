/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_gradient_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 18:00:00 by joao-alm          #+#    #+#             */
/*   Updated: 2025/11/01 19:34:45 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

t_rgb	extract_rgb(int color)
{
	t_rgb	rgb;

	rgb.r = (color >> 16) & 0xFF;
	rgb.g = (color >> 8) & 0xFF;
	rgb.b = color & 0xFF;
	return (rgb);
}

double	calculate_interpolation(int current_step, int total_steps)
{
	double	t;

	if (total_steps == 0)
		return (0.0);
	t = (double)current_step / (double)total_steps;
	if (t < 0.0)
		return (0.0);
	if (t > 1.0)
		return (1.0);
	return (t);
}

int	get_color_gradient(t_point start, t_point end, int step, int total)
{
	double	t;
	t_rgb	color_start;
	t_rgb	color_end;
	t_rgb	result;

	t = calculate_interpolation(step, total);
	color_start = extract_rgb(start.color);
	color_end = extract_rgb(end.color);
	result.r = color_start.r + (int)((color_end.r - color_start.r) * t);
	result.g = color_start.g + (int)((color_end.g - color_start.g) * t);
	result.b = color_start.b + (int)((color_end.b - color_start.b) * t);
	return ((result.r << 16) | (result.g << 8) | result.b);
}
