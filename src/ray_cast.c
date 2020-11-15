/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoss <mjoss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 04:07:48 by mjoss             #+#    #+#             */
/*   Updated: 2020/11/15 05:00:12 by mjoss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <math.h>
#include <stdio.h>

void		draw_pseudo_3d(t_wolf3d *wolf, int ray_len, float i, float player_angle, float ray_angle, t_map map)
{
	int map_size;
	int horisontal_line_size;
	int horisontal_line_start;
	int horisontal_line_finish;
	SDL_Rect	srect;
	SDL_Rect	drect;

	map_size = map.width * map.height;
	horisontal_line_size = (float)SCREEN_HEIGHT / (ray_len * cos(ray_angle - player_angle)) * map_size;
	horisontal_line_start = (SCREEN_HEIGHT - horisontal_line_size) / 2;
	horisontal_line_finish = horisontal_line_start + horisontal_line_size;


//	srect.x = i * 800;
//	srect.y = 0;
//	srect.w = 1;
//	srect.h = 680;
//
//	drect.x = i + map.width * map_size;
//	drect.y = horisontal_line_start;
//	drect.w = 1;
//	drect.h = horisontal_line_size;

//	SDL_RenderCopy(wolf->renderer, wolf->texture, &srect, &drect);
	//SDL_RenderPresent(wolf->renderer);


	SDL_SetRenderDrawColor(wolf->renderer, 255, 245, 11, 255);
	SDL_RenderDrawLine(wolf->renderer, i + map.width * map_size, horisontal_line_start,
					   i + map.width * map_size, horisontal_line_finish);

}
void		check_hor_intersection(t_map map, t_wolf3d *wolf, float x, float y, float ray_angle)
{
	float	ay;
	float	ax;
	float	xa;
	float	ya;
	int		size_map;

	size_map = map.width * map.height;
//	if ((ray_angle > M_PI && ray_angle < 2 * M_PI) || (ray_angle > 0 && ray_angle < M_PI))
//	{
		if ((ray_angle > M_PI && ray_angle < 2 * M_PI))
			ay = (int)(y / size_map) * size_map - 1;
		else
			ay = (int)(y / size_map) * size_map + size_map;
		ax = x + (ay - y) / tan(ray_angle);
		ya = ray_angle > M_PI && ray_angle < 2 * M_PI ? -size_map : size_map;
		xa = size_map / tan(ray_angle);
		while (ay > 0 && ay / size_map < map.height && ax > 0 && ax / size_map < map.width &&
			   map.map[(int)(ay / size_map)][(int)(ax / size_map)] != 1)
		{
			ax = ax + xa;
			ay = ay + ya;
		}
		SDL_SetRenderDrawColor(wolf->renderer, 255, 245, 11, 255);
		SDL_RenderDrawLine(wolf->renderer, x, y, ax, ay);
//	}
}

void		check_ver_intersection(t_map map, t_wolf3d *wolf, float x, float y, float ray_angle)
{
	float	by;
	float	bx;
	float	xa;
	float	ya;
	int		size_map;

	size_map = map.width * map.height;
	if ((ray_angle > M_PI && ray_angle < 2 * M_PI) || (ray_angle > 0 && ray_angle < M_PI))
	{
		if ((ray_angle > M_PI_2 && ray_angle < 3 * M_PI_2))
			bx = (int)(x / size_map) * size_map - 1;
		else
			bx = (int)(x / size_map) * size_map + size_map;
		by = y + (bx - x) * tan(ray_angle);
		xa = ray_angle > M_PI_2 && ray_angle < 3 * M_PI_2 ? -size_map : size_map;
		ya = size_map * tan(ray_angle);
		while (by > 0 && by / size_map < map.height && bx > 0 && bx / size_map < map.width &&
			   map.map[(int)(by / size_map)][(int)(bx / size_map)] != 1)
		{
			bx = bx + xa;
			by = by + ya;
		}
		SDL_SetRenderDrawColor(wolf->renderer, 255, 0, 11, 255);
		SDL_RenderDrawLine(wolf->renderer, x, y, bx, by);
	}
}

int			draw_ray_map(t_map map, t_wolf3d *wolf, float x, float y, float ray_angle)
{
	int ray_x;
	int ray_y;
	int ray_len;
	int	size_map;
/*
	float	ay;
	float	ax;
	float	xa;
	float	ya;

	size_map = map.width * map.height;
	if ((ray_angle > M_PI && ray_angle < 2 * M_PI) || (ray_angle > 0 && ray_angle < M_PI))
	{
		if ((ray_angle > M_PI && ray_angle < 2 * M_PI))
			ay = (int)(y / size_map) * size_map - 1;
		else
			ay = (int)(y / size_map) * size_map + size_map;
		ax = x + (y - ay) / tan(-ray_angle);
		ya = ray_angle > M_PI && ray_angle < 2 * M_PI ? -size_map : size_map;
		xa = size_map / tan(ray_angle);
		while (ay > 0 && ay / size_map < map.height && ax > 0 && ax / size_map < map.width &&
				map.map[(int)(ay / size_map)][(int)(ax / size_map)] != 1)
		{
			ax = ax + xa;
			ay = ay + ya;
		}
		SDL_SetRenderDrawColor(wolf->renderer, 255, 245, 11, 255);
		SDL_RenderDrawLine(wolf->renderer, x, y, ax, ay);
	}
*/
	if (ray_angle < 0)
		ray_angle += 2 * M_PI;
	check_hor_intersection(map, wolf, x, y, ray_angle);
//	check_ver_intersection(map, wolf, x, y, ray_angle);

//	if (map.map[ay / map.height][ax / map.width] == 1)
//	{
//		SDL_SetRenderDrawColor(wolf->renderer, 255, 245, 11, 255);
//		SDL_RenderDrawLine(wolf->renderer, x, y, ray_x, ray_y);
//	}
//	else
//	{
//		ax = ax + xa;
//		ay = ay + ya;
//	}


//	ray_len = 0;
//	size_map = map.width * map.height;
//	while (ray_len < VISIBILITY_RANGE * size_map)
//	{
//		ray_x = x + ray_len * cos(ray_angle);
//		ray_y = y + ray_len * sin(ray_angle);
//		if ((ray_x >= 0 && ray_x / size_map < map.width) && (ray_y >= 0 && ray_y / size_map < map.height) &&
//			map.map[ray_y / size_map][ray_x / size_map] == 1)
//			break;
//		ray_len++;
//	}
//	SDL_SetRenderDrawColor(wolf->renderer, 255, 245, 11, 255);
//	SDL_RenderDrawLine(wolf->renderer, x, y, ray_x, ray_y);
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
	angle_value = pow(fov, 2.0) / (SCREEN_WIDTH - map.width * map.width * map.height);
	i = 0;
	while (i < SCREEN_WIDTH - map.width * map.width * map.height)
	{
		ray_len = draw_ray_map(map, wolf, x, y, player_angle - fov / 2 + i * angle_value);
		draw_pseudo_3d(wolf, ray_len, i, player_angle, player_angle - fov / 2 + i * angle_value,  map);
		i++;
	}
}
