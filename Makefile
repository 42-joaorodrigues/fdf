# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/24 14:08:21 by joao-alm          #+#    #+#              #
#    Updated: 2025/10/24 14:08:55 by joao-alm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
# BNAME = fractol_bonus
FLAGS = -Wall -Wextra -Werror -O3 -march=native -ffast-math

SRC = src/mandatory/fdf.c src/mandatory/keyhook.c src/mandatory/util.c \
	  src/helper.c
OBJ = $(SRC:%.c=obj/%.o)

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

