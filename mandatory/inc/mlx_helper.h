/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_helper.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 17:21:06 by joao-alm          #+#    #+#             */
/*   Updated: 2025/11/01 17:21:26 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# define ESC_KEY 65307
# define W_KEY 119
# define S_KEY 115
# define A_KEY 97
# define D_KEY 100
# define Q_KEY 113
# define E_KEY 101
# define Z_KEY 122
# define X_KEY 120
# define UP_ARROW_KEY 65362
# define DOWN_ARROW_KEY 65364
# define LEFT_ARROW_KEY 65361
# define RIGHT_ARROW_KEY 65363
# define I_KEY 105
# define T_KEY 116
# define F_KEY 102

typedef struct s_img
{
	void	*ptr;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_img;
