/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoss <mjoss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 04:07:48 by mjoss             #+#    #+#             */
/*   Updated: 2020/11/25 23:12:34 by mjoss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <math.h>

void	draw_pseudo_3d(t_wolf3d *wolf, t_ray *ray, float i, t_player player)
{
	int			horisontal_line_size;
	int			horisontal_line_start;
	SDL_Rect	s;
	SDL_Rect	d;

	horisontal_line_size = (SCREEN_HEIGHT / ((ray->ray_len / wolf->factor) *
			cos(ray->ray_angle - player.angle)));
	horisontal_line_start = (SCREEN_HEIGHT - horisontal_line_size) / 2;
	d.x = i;
	d.y = horisontal_line_start;
	d.w = 1;
	d.h = horisontal_line_size;
	if (ray->hit_x == (int)ray->hit_x)
	{
		hit_x(wolf, ray, &s, &d);
	}
	else
	{
		hit_y(wolf, ray, &s, &d);
	}
}

void	draw_ray_map(t_map map, t_wolf3d *wolf, t_player player, t_ray *ray)
{
	float	ray1_len;
	float	ray2_len;
	float	ray1_len_down;
	float	ray2_len_down;
	float	ray4hit;

	if (ray->ray_angle < 0)
		ray->ray_angle += 2 * M_PI;
	if (ray->ray_angle > 2 * M_PI)
		ray->ray_angle -= 2 * M_PI;
	ray4hit = ray->ray_angle > M_PI ? ray->ray_angle - M_PI :
			ray->ray_angle + M_PI;
	ray1_len_down = draw_h_down(map, wolf, player, ray4hit);
	ray2_len_down = draw_v_down(map, wolf, player, ray4hit);
	ray1_len = draw_horisontal(map, wolf, player, ray);
	ray2_len = draw_vertical(map, wolf, player, ray);
	if (ray1_len < 15 || ray2_len < 15)
		wolf->is_hit = 1;
	if (ray1_len_down < 15 || ray2_len_down < 15)
		wolf->is_hit_down = 1;
	if (ray1_len < ray2_len)
		ray->ray_len = draw_horisontal(map, wolf, player, ray);
	else
		ray->ray_len = draw_vertical(map, wolf, player, ray);
}

/*
**  rays_count = SCREEN_WIDTH / fov
**  angle_value = fov / rays_count <==> fov / (SCREEN_WIDTH / fov)
*/

void	draw_rays(t_map map, t_wolf3d *wolf, t_player player)
{
	float	fov;
	int		i;
	float	angle_value;
	t_ray	ray[SCREEN_WIDTH];

	fov = 60 * (M_PI / 180);
	angle_value = pow(fov, 2.0) / SCREEN_WIDTH;
	i = 0;
	while (i < SCREEN_WIDTH)
	{
		ray[i].ray_angle = player.angle - fov / 2 + (float)i * angle_value;
		draw_ray_map(map, wolf, player, &ray[i]);
		draw_pseudo_3d(wolf, &ray[i], (float)i, player);
		i++;
	}
}
