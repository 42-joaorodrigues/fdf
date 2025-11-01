/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 17:22:07 by joao-alm          #+#    #+#             */
/*   Updated: 2025/11/01 19:50:01 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# define DX 0
# define DY 1

typedef struct s_limit
{
	int	min;
	int	max;
}		t_limit;

typedef struct s_point
{
	int	x;
	int	y;
	int	z;
	int	color;
}		t_point;

typedef struct s_bresenham
{
	int	dx;
	int	dy;
	int	p;
	int	step_x;
	int	step_y;
}		t_bresenham;

#endif
