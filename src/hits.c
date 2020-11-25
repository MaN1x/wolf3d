/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hits.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoss <mjoss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 22:57:57 by mjoss             #+#    #+#             */
/*   Updated: 2020/11/25 23:09:24 by mjoss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	hit_x(t_wolf3d *wolf, t_ray *ray, SDL_Rect *s, SDL_Rect *d)
{
	if (ray->ray_angle > M_PI_2 && ray->ray_angle < 3 * M_PI_2)
	{
		fill_rect_w(*wolf, *ray, s);
		SDL_RenderCopy(wolf->renderer, wolf->textures[1].west->texture,
																		s, d);
	}
	else
	{
		fill_rect_e(*wolf, *ray, s);
		SDL_RenderCopy(wolf->renderer, wolf->textures[1].east->texture,
																		s, d);
	}
}

void	hit_y(t_wolf3d *wolf, t_ray *ray, SDL_Rect *s, SDL_Rect *d)
{
	if (ray->ray_angle < M_PI)
	{
		fill_rect_s(*wolf, *ray, s);
		SDL_RenderCopy(wolf->renderer, wolf->textures[1].south->texture,
																		s, d);
	}
	else
	{
		fill_rect_n(*wolf, *ray, s);
		SDL_RenderCopy(wolf->renderer, wolf->textures[1].north->texture,
																		s, d);
	}
}
