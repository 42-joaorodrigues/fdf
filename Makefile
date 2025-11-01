# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/24 14:08:21 by joao-alm          #+#    #+#              #
#    Updated: 2025/11/01 19:16:19 by joao-alm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= fdf
BNAME	= fdf_bonus

CC		= cc
FLAGS	= -Wall -Wextra -Werror \
		  -O3 -march=native -ffast-math \
		  -Wno-incompatible-pointer-types

# libs
MLX		= lib/mlx/libmlx.a
MLXINC	= -I lib/mlx
MLXL	= -Llib/mlx -lmlx -lXext -lX11 -lm

LIBFT	= lib/libft/libft.a
LIBFTIN	= -I lib/libft
LIBFTL	= -Llib/libft -lft

# mandatory files
INC		= -I mandatory/inc $(MLXINC) $(LIBFTIN)
SRC		= main.c \
		  \
		  parser.c \
		  \
		  input/handle_key.c \
		  input/keyhook.c \
		  \
		  projection/projection.c \
		  projection/rotation.c \
		  projection/views.c \
		  \
		  render/color_gradient.c \
		  render/draw_fdf.c \
		  render/draw_util.c \
		  render/line_draw.c \
		  \
		  util/color.c \
		  util/exit.c \
		  util/limits.c
SRC		:= $(addprefix mandatory/src/, $(SRC))
OBJ		= $(SRC:%.c=obj/%.o)

# bonus files
BINC	= -I bonus/inc
BSRC	= main_bonus.c \
		  \
		  parser_bonus.c \
		  \
		  input/handle_key_bonus.c \
		  input/keyhook_bonus.c \
		  \
		  projection/projection_bonus.c \
		  projection/rotation_bonus.c \
		  projection/views_bonus.c \
		  \
		  render/color_gradient_bonus.c \
		  render/draw_fdf_bonus.c \
		  render/draw_util_bonus.c \
		  render/line_draw_bonus.c \
		  \
		  util/color_bonus.c \
		  util/exit_bonus.c \
		  util/limits_bonus.c
BSRC	:= $(addprefix bonus/src/, $(BSRC))
BOBJ	= $(BSRC:%.c=obj/%.o)

# compile libs and fdf
all: $(LIBFT) $(NAME)

# compile libs
$(MLX):
	make -C lib/mlx

$(LIBFT):
	make -C lib/libft

# compile from .c to .o inside obj/
obj/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(FLAGS) -c $< -o $@ $(MLXINC) $(LIBFTIN) $(INC) $(BINC)

# compile fdf
$(NAME): $(OBJ)
	$(CC) $^ -o $@ $(MLXL) $(LIBFTL)

# compile libs and fdf_bonus
bonus: $(MLX) $(LIBFT) $(BNAME)

# compile fdf_bonus
$(BNAME): $(BOBJ)
	$(CC) $^ -o $@ $(MLXL) $(LIBFTL)

clean:
	make -C lib/libft clean
	rm -rf obj

fclean: clean
# 	make -C lib/mlx clean
	make -C lib/libft fclean
	rm -rf $(NAME)
	rm -rf $(BNAME)

re: fclean all bonus

.PHONY: all clean fclean re
