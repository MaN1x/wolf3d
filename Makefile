# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: npetrell <npetrell@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/13 04:12:40 by mjoss             #+#    #+#              #
#    Updated: 2020/11/26 19:11:52 by mjoss            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	wolf3d

FLAGS = -Wall -Wextra -Werror

SRC		=	main.c			\
			init_sdl.c		\
			destroy_sdl.c	\
			parse_map.c		\
			draw_map.c		\
			draw_player.c	\
			ray_cast.c		\
			texture_loader.c\
			logo_draw.c		\
			button_draw.c	\
			button_init.c	\
			text_output_sett.c \
			fill_rect.c		\
			find_walls.c	\
			hits.c			\
			controls.c		\
			draw.c			\
			parse_map2.c	\
			parse_map3.c	\

HEADERS	=	map_parser.h	\
			wolf3d.h		\

SRC_DIR = src/
OBJ_DIR = obj/
HEADERS_DIR = include/

SRC_FILES = $(addprefix $(SRC_DIR), $(SRC))
OBJ_FILES = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))
HEADER_FILES = $(addprefix $(HEADERS_DIR), $(HEADERS))

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ_FILES)
	gcc $(FLAGS) -g -L lib -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -L libft -lft $(OBJ_FILES) -o $(NAME)

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADER_FILES)
	gcc $(FLAGS) -g -I include -I libft/includes -o $@ -c $<

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm $(NAME)

re: fclean all

.PHONY: all fclean clean re
