/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoss <mjoss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 04:07:48 by mjoss             #+#    #+#             */
/*   Updated: 2020/11/19 13:30:33 by mjoss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <math.h>

void		draw_pseudo_3d(t_wolf3d *wolf, t_ray *ray, float i, float player_angle, t_map map)
{
	int map_size;
	int horisontal_line_size;
	int horisontal_line_start;

	SDL_Rect	srect;
	SDL_Rect	drect;

	map_size = map.width * map.height;
	horisontal_line_size = (SCREEN_HEIGHT / ((float)ray->ray_len / wolf->factor * cos(ray->ray_angle - player_angle)));
	horisontal_line_start = (SCREEN_HEIGHT - horisontal_line_size) / 2;

	drect.x = i;
	drect.y = horisontal_line_start;
	drect.w = 1;
	drect.h = horisontal_line_size;

	if (ray->hit_x != 0)
	{
		srect.x = ray->hit_x * 800;
		srect.y = 0;
		srect.w = 1;
		srect.h = 680;
	}
	else
	{
		srect.x = ray->hit_y * 800;
		srect.y = 0;
		srect.w = 1;
		srect.h = 680;
	}
	if (horisontal_line_start < 0)
	{
		srect.y = horisontal_line_start / 680 * -1;
		horisontal_line_start = 0;
		horisontal_line_size = SCREEN_HEIGHT;
	}
	SDL_RenderCopy(wolf->renderer, wolf->texture, &srect, &drect);
}

int			draw_ray_map(t_map map, t_wolf3d *wolf, float player_x, float player_y, t_ray *ray)
{
	float ray_x;
	float ray_y;
	int ray_len;

	float mod_ray_x;
	float mod_ray_y;

	ray_len = 0;
	while (ray_len < VISIBILITY_RANGE * wolf->factor)
	{
		ray_x = player_x + ray_len * cos(ray->ray_angle);
		ray_y = player_y + ray_len * sin(ray->ray_angle);
		if ((ray_x >= 0 && (int)(ray_x / wolf->factor) < map.width) && (ray_y >= 0 && (int)(ray_y / wolf->factor) < map.height) &&
			map.map[(int)(ray_y / wolf->factor)][(int)(ray_x / wolf->factor)] == 1)
			break;
		ray_len++;
	}

	mod_ray_x = ray_x  - (int)(ray_x / wolf->factor) * wolf->factor;
	mod_ray_y = ray_y  - (int)(ray_y / wolf->factor) * wolf->factor;

	if (M_PI_2 > ray->ray_angle)
	{
		if ((int)mod_ray_y == 0)
		{
			SDL_SetRenderDrawColor(wolf->renderer, 255, 255, 11, 255);
			ray->hit_x = mod_ray_x / wolf->factor;
			ray->hit_y = 0;
		}
		else
		{
			SDL_SetRenderDrawColor(wolf->renderer, 255, 0, 11, 255);
			ray->hit_y = mod_ray_y / wolf->factor;
			ray->hit_x = 0;
		}
	}
	else
	{
		mod_ray_x = (ray_x - wolf->factor)  - (int)((ray_x - wolf->factor) / wolf->factor) * wolf->factor;
		mod_ray_y = (ray_y - wolf->factor)  - (int)((ray_y - wolf->factor) / wolf->factor) * wolf->factor;
		if ((int)mod_ray_y == 0)
		{
			SDL_SetRenderDrawColor(wolf->renderer, 255, 255, 11, 255);
			ray->hit_x = mod_ray_x / wolf->factor;
			ray->hit_y = 0;
		}
		else
		{
			SDL_SetRenderDrawColor(wolf->renderer, 255, 0, 11, 255);
			ray->hit_y = mod_ray_y / wolf->factor;
			ray->hit_x = 0;
		}
	}
	SDL_RenderDrawLine(wolf->renderer,
					(int)(player_x / wolf->factor * (int)((SCREEN_WIDTH * SIZE_MAP) / wolf->map->width)),
					(int)(player_y / wolf->factor * (int)((SCREEN_HEIGHT * SIZE_MAP) / wolf->map->height)),
					(int)(ray_x / wolf->factor * (int)((SCREEN_WIDTH * SIZE_MAP) / wolf->map->width)),
					(int)(ray_y / wolf->factor * (int)((SCREEN_HEIGHT * SIZE_MAP) / wolf->map->height)));
	return (ray_len);
}

/*
**  rays_count = SCREEN_WIDTH / fov
**  angle_value = fov / rays_count <==> fov / (SCREEN_WIDTH / fov)
*/


void			draw_rays(t_map map, t_wolf3d *wolf, float player_x, float player_y, float player_angle)
{
	float	fov;
	int 	i;
	float	angle_value;
	t_ray	ray[SCREEN_WIDTH];

	fov = 60 * (M_PI / 180);
	angle_value = pow(fov, 2.0) / SCREEN_WIDTH;
	i = 0;
	while (i < SCREEN_WIDTH)
	{
		ray[i].ray_angle = player_angle - fov / 2 + (float)i * angle_value;
		ray[i].ray_len = draw_ray_map(map, wolf, player_x, player_y, &ray[i]);
		if (i == SCREEN_WIDTH / 2 && ray[i].ray_len < 28)
        	wolf->is_hit = 1;
		draw_pseudo_3d(wolf, &ray[i], (float)i, player_angle, map);
		i++;
	}
}
