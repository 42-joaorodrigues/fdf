# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/24 14:08:21 by joao-alm          #+#    #+#              #
#    Updated: 2025/11/01 14:30:05 by joao-alm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= fdf
# BNAME = fractol_bonus
# -Wall -Wextra -Werror
FLAGS	= -Wall -Wextra -Werror -Wno-incompatible-pointer-types -O3 -march=native -ffast-math

HELPER	= atoi_base.c atoi.c free_split.c ft_split.c gnl_util.c gnl.c util.c
HELPER	:= $(addprefix src/helper/, $(HELPER))

SRC 	= fdf.c draw.c keyhook.c parser.c prep.c util.c
SRC		:= $(addprefix src/mandatory/, $(SRC)) $(HELPER)
OBJ		= $(SRC:%.c=obj/%.o)

# BSRC = 
# BOBJ = $(BSRC:%.c=obj/%.o)

all: $(NAME)

bonus: $(BNAME)

obj/%.o: %.c
	mkdir -p $(dir $@)
	cc $(FLAGS) -c $< -o $@ -Iinc -Iccmlx

$(NAME): $(OBJ)
	cc $^ -o $@ -Lccmlx -lmlx -lXext -lX11 -lm

# $(BNAME): $(BOBJ)
# 	cc $^ -o $@ -Lccmlx -lmlx -lXext -lX11 -lm

clean:
	rm -rf obj

fclean: clean
	rm -rf $(NAME)
# 	rm -rf $(BNAME)

re: fclean all bonus

.PHONY: all clean fclean re

