/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoss <mjoss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 04:07:48 by mjoss             #+#    #+#             */
/*   Updated: 2020/11/13 17:56:43 by mjoss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <math.h>

void		draw_pseudo_3d(t_wolf3d *wolf, int ray_len, float i, float player_angle, float ray_angle, t_map map)
{
	int map_size;
	int horisontal_line_size;
	int horisontal_line_start;
	int horisontal_line_finish;

	map_size = map.width * map.height;
	horisontal_line_size = (float)SCREEN_HEIGHT / (ray_len * cos(ray_angle - player_angle)) * map_size;
	horisontal_line_start = (SCREEN_HEIGHT - horisontal_line_size) / 2;
	horisontal_line_finish = horisontal_line_start + horisontal_line_size;
	SDL_SetRenderDrawColor(wolf->renderer, 255, 245, 11, 255);
	SDL_RenderDrawLine(wolf->renderer, i + map.width * map_size, horisontal_line_start,
					   i + map.width * map_size, horisontal_line_finish);
}

int			draw_ray_map(t_map map, t_wolf3d *wolf, float x, float y, float ray_angle)
{
	int ray_x;
	int ray_y;
	int ray_len;
	int	size_map;

	ray_len = 0;
	size_map = map.width * map.height;
	while (ray_len < VISIBILITY_RANGE * size_map)
	{
		ray_x = x + ray_len * cos(ray_angle);
		ray_y = y + ray_len * sin(ray_angle);
		if ((ray_x >= 0 && ray_x / size_map < map.width) && (ray_y >= 0 && ray_y / size_map < map.height) &&
			map.map[ray_x / size_map][ray_y / size_map] == 1)
			break;
		ray_len++;
	}
	SDL_SetRenderDrawColor(wolf->renderer, 255, 245, 11, 255);
	SDL_RenderDrawLine(wolf->renderer, x, y, ray_x, ray_y);
	return (ray_len);
}

/*
**  rays_count = SCREEN_WIDTH / fov
**  angle_value = fov / rays_count <==> fov / (SCREEN_WIDTH / fov)
*/


void			draw_rays(t_map map, t_wolf3d *wolf, float x, float y, float player_angle)
{
	float	fov;
	float 	i;
	float	angle_value;
	int 	ray_len;

	fov = 60 * (M_PI / 180);
	angle_value = pow(fov, 2.0) / SCREEN_WIDTH;
	i = 0;
	while (i < SCREEN_WIDTH)
	{
		ray_len = draw_ray_map(map, wolf, x, y, player_angle - fov / 2 + i * angle_value);
		draw_pseudo_3d(wolf, ray_len, i, player_angle, player_angle - fov / 2 + i * angle_value,  map);
		i++;
	}
}
