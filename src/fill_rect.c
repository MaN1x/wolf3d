/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_rect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoss <mjoss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 22:27:56 by mjoss             #+#    #+#             */
/*   Updated: 2020/11/25 22:29:09 by mjoss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	fill_rect_e(t_wolf3d wolf, t_ray ray, SDL_Rect *rect)
{
	int	i;

	i = 1;
	rect->x = (fabs(ray.hit_y - (int)(ray.hit_y / wolf.factor) * wolf.factor) /
			wolf.factor) * wolf.textures[i].east->image->w;
	rect->y = 0;
	rect->w = 1;
	rect->h = wolf.textures[i].east->image->h;
}

void	fill_rect_n(t_wolf3d wolf, t_ray ray, SDL_Rect *rect)
{
	int	i;

	i = 1;
	rect->x = (fabs(ray.hit_x - (int)(ray.hit_x / wolf.factor) * wolf.factor) /
			wolf.factor) * wolf.textures[i].north->image->w;
	rect->y = 0;
	rect->w = 1;
	rect->h = wolf.textures[i].north->image->h;
}

void	fill_rect_w(t_wolf3d wolf, t_ray ray, SDL_Rect *rect)
{
	int	i;

	i = 1;
	rect->x = (fabs(ray.hit_y - (int)(ray.hit_y / wolf.factor) * wolf.factor) /
			wolf.factor) * wolf.textures[i].west->image->w;
	rect->y = 0;
	rect->w = 1;
	rect->h = wolf.textures[i].west->image->h;
}

void	fill_rect_s(t_wolf3d wolf, t_ray ray, SDL_Rect *rect)
{
	int	i;

	i = 1;
	rect->x = (fabs(ray.hit_x - (int)(ray.hit_x / wolf.factor) * wolf.factor) /
			wolf.factor) * wolf.textures[i].south->image->w;
	rect->y = 0;
	rect->w = 1;
	rect->h = wolf.textures[i].south->image->h;
}
