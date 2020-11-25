# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: npetrell <npetrell@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/13 04:12:40 by mjoss             #+#    #+#              #
#    Updated: 2020/11/25 21:04:34 by npetrell         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	wolf3d

SRC		=	main.c			\
			init_sdl.c		\
			destroy_sdl.c	\
			parse_map.c		\
			draw_map.c		\
			draw_player.c	\
			ray_cast.c		\
			texture_loader.c	\
			logo_draw.c	\
			button_draw.c	\
			button_init.c	\
			text_output_sett.c \

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
	gcc -g -L lib -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -L libft -lft $(OBJ_FILES) -o $(NAME)

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADER_FILES)
	gcc -g -I include -I libft/includes -o $@ -c $<

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm $(NAME)

re: fclean all

.PHONY: all fclean clean re
