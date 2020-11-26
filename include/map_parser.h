/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoss <mjoss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 15:50:01 by mjoss             #+#    #+#             */
/*   Updated: 2020/11/26 19:10:42 by mjoss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_PARSER_H
# define MAP_PARSER_H
# define BUFF_SIZE 10
# define PLAYER_CHARACTER 'X'
# include "libft.h"
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>

typedef struct	s_position
{
	int x;
	int y;
}				t_position;

typedef struct	s_map
{
	int			width;
	int			height;
	t_position	player_position;
	int			**map;
}				t_map;

int				parse_map(char *path, t_map *map);
int				get_map_len(char *path);
int				cpy_map(char *path, char *map_tmp);
int				get_map_width(const char *map_tmp);
int				get_map_height(const char *map_tmp);
int				create_mass(t_map *map);
void			from_char2struct(t_map *map, char *map_tmp);

#endif
