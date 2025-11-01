/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 17:22:07 by joao-alm          #+#    #+#             */
/*   Updated: 2025/11/01 18:24:16 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define DX 0
#define DY 1

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}		t_rgb;

typedef struct s_limit
{
	int	min;
	int	max;
}		t_limit;

typedef struct s_point
{
	int		x;
	int		y;
	int		z;
	int		color;
}			t_point;

typedef struct s_bresenham
{
	int	dx;
	int	dy;
	int	p;
	int	step_x;
	int	step_y;
}		t_bresenham;
