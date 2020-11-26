/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoss <mjoss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 19:05:32 by mjoss             #+#    #+#             */
/*   Updated: 2020/11/26 19:08:39 by mjoss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_parser.h"

int	create_mass(t_map *map)
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

int	get_map_height(const char *map_tmp)
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

int	get_map_width(const char *map_tmp)
{
	int width;

	width = 0;
	while (map_tmp[width] != '\n' && map_tmp[width] != '\0')
		width++;
	return (width);
}

int	cpy_map(char *path, char *map_tmp)
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

int	get_map_len(char *path)
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
