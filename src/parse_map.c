/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoss <mjoss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 16:00:08 by mjoss             #+#    #+#             */
/*   Updated: 2020/11/10 20:58:37 by mjoss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_parser.h"
#include "libft.h"
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

static int	get_map_len(char *path)
{
	int		map_len;
	char	buf[BUFF_SIZE];
	int		rd;
	int		fd;

	if ((fd = open(path, O_RDONLY)) == -1)
	{
		perror(path);
		return (-1);
	}
	map_len = 0;
	while ((rd = read(fd, buf, BUFF_SIZE)) > 0)
		map_len += rd;
	if (rd == -1)
	{
		perror(NULL);
		close(fd);
		return (-1);
	}
	close(fd);
	return (map_len);
}

static int	cpy_map(char *path, char *map_tmp)
{
	int	fd;
	int rd;
	int i;
	int	buf[BUFF_SIZE];

	i = 0;
	if ((fd = open(path, O_RDONLY)) == -1)
	{
		perror(path);
		return (-1);
	}
	while ((rd = read(fd, buf, BUFF_SIZE)) > 0)
	{
		ft_strncpy(&map_tmp[i], (const char*)buf, rd);
		i += rd;
	}
	if (rd == -1)
	{
		perror(NULL);
		close(fd);
		return (-1);
	}
	close(fd);
	return (1);
}

static int	get_map_width(const char *map_tmp)
{
	int width;

	width = 0;
	while (map_tmp[width] != '\n' && map_tmp[width] != '\0')
		width++;
	return (width);
}

static int	get_map_height(const char *map_tmp)
{
	int height;

	height = 0;
	while (*map_tmp)
	{
		if (*map_tmp == '\n')
			height++;
		map_tmp++;
	}
	return (height);
}

static int	create_mass(t_map *map)
{
	int i;

	i = 0;
	if (!(map->map = (int**)malloc(sizeof(int*) * map->height)))
		return (-1);
	while (i < map->height)
	{
		if (!(map->map[i] = (int*)(malloc(sizeof(int) * map->width))))
			return (-1);
		i++;
	}
	return (0);
}

static void	from_char2struct(t_map *map, char *map_tmp)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (j < map->height)
	{
		while (i < map->width)
		{
			if (*map_tmp == PLAYER_CHARACTER)
			{
				map->player_position.x = i;
				map->player_position.y = j;
				*map_tmp = '0';
			}
			if (!ft_isdigit(*map_tmp))
			{
				map_tmp++;
				continue;
			}
			map->map[j][i] = *map_tmp - '0';
			map_tmp++;
			i++;
		}
		i = 0;
		j++;
	}
}

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
		width = i;
	else
		return (0);
	while (map_tmp[++i])
	{
		if (map_tmp[i] == '\n')
		{
			if (counter == width)
				counter = 0;
			else
				return (0);
			i++;
		}
		counter++;
	}
	return (1);
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
	return (check_map_width(map_tmp) && check_map_symbols(map_tmp));
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
