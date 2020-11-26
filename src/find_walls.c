/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoss <mjoss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 22:29:51 by mjoss             #+#    #+#             */
/*   Updated: 2020/11/26 18:17:46 by mjoss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		check_wall(int x, int y, t_map map)
{
	if (x > 0 && x < map.width && y > 0 && y < map.height && map.map[y][x] != 1)
		return (1);
	return (0);
}

float	draw_vertical(t_wolf3d *wlf, t_player player, t_ray *ray)
{
	float	r_xy[2];
	float	step_x;
	float	step_y;
	float	ray_angle;

	ray_angle = ray->ray_angle;
	step_x = ray_angle < M_PI_2 || ray_angle > 3 * M_PI_2 ?
			wlf->factor : -wlf->factor;
	if (ray_angle < M_PI_2 || ray_angle > 3 * M_PI_2)
		r_xy[0] = (int)(player.x / wlf->factor) * wlf->factor + wlf->factor;
	else
	{
		ray_angle = 2 * M_PI - ray_angle;
		r_xy[0] = (int)(player.x / wlf->factor) * wlf->factor - 1;
	}
	step_y = wlf->factor * tan(ray_angle);
	r_xy[1] = player.y + (fabs(player.x - r_xy[0])) * tan(ray_angle);
	while (check_wall(r_xy[0] / wlf->factor, r_xy[1] / wlf->factor, *wlf->map))
	{
		r_xy[0] += step_x;
		r_xy[1] += step_y;
	}
	ray->hit_x = r_xy[0];
	ray->hit_y = r_xy[1];
	return (sqrt(pow(player.x - r_xy[0], 2.0) + pow(player.y - r_xy[1], 2.0)));
}

float	draw_horisontal(t_wolf3d *wolf, t_player player, t_ray *ray)
{
	float	ray_x;
	float	ray_y;
	float	step_x;
	float	step_y;
	float	ray_angle;

	ray_angle = ray->ray_angle;
	step_y = ray_angle < M_PI ? wolf->factor : -wolf->factor;
	if (ray_angle < M_PI)
		ray_y = (int)(player.y / wolf->factor) * wolf->factor + wolf->factor;
	else
	{
		ray_angle = 2 * M_PI - ray_angle;
		ray_y = (int)(player.y / wolf->factor) * wolf->factor - 1;
	}
	step_x = wolf->factor / tan(ray_angle);
	ray_x = player.x + (fabs(player.y - ray_y)) / tan(ray_angle);
	while (check_wall(ray_x / wolf->factor, ray_y / wolf->factor, *wolf->map))
	{
		ray_x += step_x;
		ray_y += step_y;
	}
	ray->hit_x = ray_x;
	ray->hit_y = ray_y;
	return (sqrt(pow(player.x - ray_x, 2.0) + pow(player.y - ray_y, 2.0)));
}

float	draw_v_down(t_wolf3d *wolf, t_player player, float ray_angle)
{
	float	ray_x;
	float	ray_y;
	float	step_x;
	float	step_y;

	step_x = ray_angle < M_PI_2 || ray_angle > 3 * M_PI_2 ?
			wolf->factor : -wolf->factor;
	if (ray_angle < M_PI_2 || ray_angle > 3 * M_PI_2)
		ray_x = (int)(player.x / wolf->factor) * wolf->factor + wolf->factor;
	else
	{
		ray_angle = 2 * M_PI - ray_angle;
		ray_x = (int)(player.x / wolf->factor) * wolf->factor - 1;
	}
	step_y = wolf->factor * tan(ray_angle);
	ray_y = player.y + (fabs(player.x - ray_x)) * tan(ray_angle);
	while (check_wall(ray_x / wolf->factor, ray_y / wolf->factor, *wolf->map))
	{
		ray_x += step_x;
		ray_y += step_y;
	}
	return (sqrt(pow(player.x - ray_x, 2.0) + pow(player.y - ray_y, 2.0)));
}

float	draw_h_down(t_wolf3d *wolf, t_player player, float ray_angle)
{
	float	ray_x;
	float	ray_y;
	float	step_x;
	float	step_y;

	step_y = ray_angle < M_PI ? wolf->factor : -wolf->factor;
	if (ray_angle < M_PI)
		ray_y = (int)(player.y / wolf->factor) * wolf->factor + wolf->factor;
	else
	{
		ray_angle = 2 * M_PI - ray_angle;
		ray_y = (int)(player.y / wolf->factor) * wolf->factor - 1;
	}
	step_x = wolf->factor / tan(ray_angle);
	ray_x = player.x + (fabs(player.y - ray_y)) / tan(ray_angle);
	while (check_wall(ray_x / wolf->factor, ray_y / wolf->factor, *wolf->map))
	{
		ray_x += step_x;
		ray_y += step_y;
	}
	return (sqrt(pow(player.x - ray_x, 2.0) + pow(player.y - ray_y, 2.0)));
}
