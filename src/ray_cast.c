/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoss <mjoss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 04:07:48 by mjoss             #+#    #+#             */
/*   Updated: 2020/11/24 04:27:53 by mjoss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <math.h>

void		fill_rect_e(t_wolf3d wolf, t_ray ray, SDL_Rect *rect)
{
	int	i;

	i = 1;
	rect->x = (fabs(ray.hit_y - (int)(ray.hit_y / wolf.factor) * wolf.factor) / wolf.factor) * wolf.textures[i].east->image->w;
	rect->y = 0;
	rect->w = 1;
	rect->h = wolf.textures[i].east->image->h;
}

void		fill_rect_n(t_wolf3d wolf, t_ray ray, SDL_Rect *rect)
{
	int	i;

	i = 1;
	rect->x = (fabs(ray.hit_x - (int)(ray.hit_x / wolf.factor) * wolf.factor) / wolf.factor) * wolf.textures[i].north->image->w;
	rect->y = 0;
	rect->w = 1;
	rect->h = wolf.textures[i].north->image->h;
}

void		fill_rect_w(t_wolf3d wolf, t_ray ray, SDL_Rect *rect)
{
	int	i;

	i = 1;
	rect->x = (fabs(ray.hit_y - (int)(ray.hit_y / wolf.factor) * wolf.factor) / wolf.factor) * wolf.textures[i].west->image->w;
	rect->y = 0;
	rect->w = 1;
	rect->h = wolf.textures[i].west->image->h;
}

void		fill_rect_s(t_wolf3d wolf, t_ray ray, SDL_Rect *rect)
{
	int	i;

	i = 1;
	rect->x = (fabs(ray.hit_x - (int)(ray.hit_x / wolf.factor) * wolf.factor) / wolf.factor) * wolf.textures[i].south->image->w;
	rect->y = 0;
	rect->w = 1;
	rect->h = wolf.textures[i].south->image->h;
}

void		draw_pseudo_3d(t_wolf3d *wolf, t_ray *ray, float i, t_player player, t_map map)
{
	int	horisontal_line_size;
	int	horisontal_line_start;

	SDL_Rect	srect;
	SDL_Rect	drect;

	horisontal_line_size = (SCREEN_HEIGHT / ((ray->ray_len / wolf->factor) * cos(ray->ray_angle - player.angle)));
	horisontal_line_start = (SCREEN_HEIGHT - horisontal_line_size) / 2;

	drect.x = i;
	drect.y = horisontal_line_start;
	drect.w = 1;
	drect.h = horisontal_line_size;

	if (ray->hit_x == (int)ray->hit_x)
	{
		if (ray->ray_angle > M_PI_2 && ray->ray_angle < 3 * M_PI_2)
		{
			fill_rect_w(*wolf, *ray, &srect);
			SDL_RenderCopy(wolf->renderer, wolf->textures[1].west->texture, &srect, &drect);
		}
		else
		{
			fill_rect_e(*wolf, *ray, &srect);
			SDL_RenderCopy(wolf->renderer, wolf->textures[1].east->texture, &srect, &drect);
		}
	}
	else
	{
		if (ray->ray_angle < M_PI)
		{
			fill_rect_s(*wolf, *ray, &srect);
			SDL_RenderCopy(wolf->renderer, wolf->textures[1].south->texture, &srect, &drect);
		}
		else
		{
			fill_rect_n(*wolf, *ray, &srect);
			SDL_RenderCopy(wolf->renderer, wolf->textures[1].north->texture, &srect, &drect);
		}


	}
}

float		draw_vertical(t_map map, t_wolf3d *wolf, t_player player, t_ray *ray)
{
	float	ray_x;
	float	ray_y;
	float	stepX;
	float	stepY;
	float	ray_angle;

	ray_angle = ray->ray_angle;
	if (ray_angle < M_PI_2 || ray_angle > 3 * M_PI_2)
	{
		ray_x = (int)(player.x / wolf->factor) * wolf->factor  + wolf->factor;
		stepX = wolf->factor;
	}
	else
	{
		ray_angle = 2 * M_PI - ray_angle;
		ray_x = (int)(player.x / wolf->factor) * wolf->factor - 1;
		stepX = -wolf->factor;
	}
	stepY = wolf->factor * tan(ray_angle);
	ray_y = player.y + (fabs(player.x  - ray_x)) * tan(ray_angle);
	while (ray_y / wolf->factor > 0 && ray_y / wolf->factor < map.height &&
		   ray_x / wolf->factor > 0 && ray_x / wolf->factor < map.width &&
		   map.map[(int)(ray_y / wolf->factor)][(int)(ray_x / wolf->factor)] != 1)
	{
		ray_x += stepX;
		ray_y += stepY;
	}
	ray->hit_x = ray_x;
	ray->hit_y = ray_y;
	return (sqrt(pow(player.x - ray_x, 2.0) + pow(player.y - ray_y, 2.0)));
}

float		draw_horisontal(t_map map, t_wolf3d *wolf, t_player player, t_ray *ray)
{
	float	ray_x;
	float	ray_y;
	float	stepX;
	float	stepY;
	float	ray_angle;

	ray_angle = ray->ray_angle;
	if (ray_angle < M_PI)
	{
		ray_y = (int)(player.y / wolf->factor) * wolf->factor + wolf->factor;
		stepY = wolf->factor;
	}
	else
	{
		ray_angle = 2 * M_PI - ray_angle;
		ray_y = (int)(player.y / wolf->factor) * wolf->factor - 1;
		stepY = -wolf->factor;
	}
	stepX = wolf->factor / tan(ray_angle);
	ray_x = player.x + (fabs(player.y  - ray_y)) / tan(ray_angle);
	while (ray_y / wolf->factor > 0 && ray_y / wolf->factor < map.height &&
		   ray_x / wolf->factor > 0 && ray_x / wolf->factor < map.width &&
		   map.map[(int)(ray_y / wolf->factor)][(int)(ray_x / wolf->factor)] != 1)
	{
		ray_x += stepX;
		ray_y += stepY;
	}
	ray->hit_x = ray_x;
	ray->hit_y = ray_y;
	return (sqrt(pow(player.x - ray_x, 2.0) + pow(player.y - ray_y, 2.0)));
}

void			draw_ray_map(t_map map, t_wolf3d *wolf, t_player player, t_ray *ray)
{
	float	ray1_len;
	float	ray2_len;

	if (ray->ray_angle < 0)
		ray->ray_angle += 2 * M_PI;
	if (ray->ray_angle > 2 * M_PI)
		ray->ray_angle -= 2 * M_PI;
	ray1_len = draw_horisontal(map, wolf, player, ray);
	ray2_len = draw_vertical(map, wolf, player, ray);
	if (ray1_len < ray2_len)
	{
		SDL_SetRenderDrawColor(wolf->renderer, 255, 255, 11, 255);
		ray->ray_len = draw_horisontal(map, wolf, player, ray);
	}
	else
	{
		SDL_SetRenderDrawColor(wolf->renderer, 255, 0, 11, 255);
		ray->ray_len = draw_vertical(map, wolf, player, ray);
	}

	SDL_RenderDrawLine(wolf->renderer,
					   (int)(player.x / wolf->factor * (int)((SCREEN_WIDTH * SIZE_MAP) / wolf->map->width)),
					   (int)(player.y / wolf->factor * (int)((SCREEN_HEIGHT * SIZE_MAP) / wolf->map->height)),
					   (int)(ray->hit_x / wolf->factor * (int)((SCREEN_WIDTH * SIZE_MAP) / wolf->map->width)),
					   (int)(ray->hit_y / wolf->factor * (int)((SCREEN_HEIGHT * SIZE_MAP) / wolf->map->height)));
}

/*
**  rays_count = SCREEN_WIDTH / fov
**  angle_value = fov / rays_count <==> fov / (SCREEN_WIDTH / fov)
*/


void			draw_rays(t_map map, t_wolf3d *wolf, t_player player)
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
		ray[i].ray_angle = player.angle - fov / 2 + (float)i * angle_value;
		draw_ray_map(map, wolf, player, &ray[i]);
		if (i == SCREEN_WIDTH / 2 && ray[i].ray_len < 28)
        	wolf->is_hit = 1;
		draw_pseudo_3d(wolf, &ray[i], (float)i, player, map);
		i++;
	}
}
