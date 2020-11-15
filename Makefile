# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mjoss <mjoss@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/13 04:12:40 by mjoss             #+#    #+#              #
#    Updated: 2020/11/13 04:26:13 by mjoss            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	wolf3d

SRC		=	main.c			\
			init_sdl.c		\
			put_pixel_sdl.c	\
			destroy_sdl.c	\
			parse_map.c		\
			draw_map.c		\
			draw_player.c	\
			ray_cast.c		\

SRC_DIR = src/
OBJ_DIR = obj/

SRC_FILES = $(addprefix $(SRC_DIR), $(SRC))
OBJ_FILES = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ_FILES)
	gcc -g -L lib -lSDL2 -lSDL2_image -L libft -lft $(OBJ_FILES) -o $(NAME)

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	gcc -I include -I libft/includes -g -o $@ -c $<

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm $(NAME)

re: fclean all

.PHONY: all fclean clean re
