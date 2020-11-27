/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoss <mjoss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 16:00:08 by mjoss             #+#    #+#             */
/*   Updated: 2020/11/27 21:08:44 by mjoss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_parser.h"

static int	fill_struct_map(t_map *map, char *map_tmp)
{
	map->width = get_map_width(map_tmp);
	map->height = get_map_height(map_tmp);
	if (create_mass(map) == -1)
		return (-1);
	from_char2struct(map, map_tmp);
	return (0);
}

static int	check_map_width(const char *map_tmp)
{
	int i;
	int counter;
	int width;

	i = 0;
	counter = 0;
	while (map_tmp[i] != '\n' && map_tmp[i])
		i++;
	if (map_tmp[i] == '\n')
		width = i++;
	else
		return (0);
	while (map_tmp[i])
	{
		if (map_tmp[i] == '\n')
			if (counter == width)
				counter = 0;
			else
				return (0);
		else
			counter++;
		i++;
	}
	return (counter == 0 ? 1 : 0);
}

static int	check_map_symbols(const char *map_tmp)
{
	int i;

	i = 0;
	while (map_tmp[i])
	{
		if (!ft_isdigit(map_tmp[i]) &&
				map_tmp[i] != PLAYER_CHARACTER && map_tmp[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

static int	check_map(const char *map_tmp)
{
	return (check_map_width(map_tmp) &&
			check_map_symbols(map_tmp) &&
			check_character(map_tmp));
}

int			parse_map(char *path, t_map *map)
{
	int		map_len;
	char	*map_tmp;

	if ((map_len = get_map_len(path)) == -1)
		return (0);
	if (!(map_tmp = ft_strnew(map_len)))
	{
		perror(NULL);
		return (0);
	}
	if (cpy_map(path, map_tmp) == -1)
	{
		free(map_tmp);
		return (0);
	}
	if (check_map(map_tmp) == 0)
		return (-1);
	if (fill_struct_map(map, map_tmp) == -1)
		return (0);
	free(map_tmp);
	return (1);
}
