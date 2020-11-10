/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoss <mjoss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 15:50:01 by mjoss             #+#    #+#             */
/*   Updated: 2020/11/09 19:18:43 by mjoss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_PARSER_H
# define MAP_PARSER_H
# define BUFF_SIZE 10
# define PLAYER_CHARACTER 'X'

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

#endif
