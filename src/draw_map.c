/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetrell <npetrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 21:25:43 by npetrell          #+#    #+#             */
/*   Updated: 2020/11/25 21:47:08 by npetrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			rect_draw(t_wolf3d *wolf, t_position position,
															t_color color)
{
	SDL_Rect	r;

	r.w = (SCREEN_WIDTH * SIZE_MAP) / wolf->map->width;
	r.h = (SCREEN_HEIGHT * SIZE_MAP) / wolf->map->height;
	r.x = position.x * r.w;
	r.y = position.y * r.h;
	SDL_SetRenderDrawColor(wolf->renderer, color.r, color.g, color.b,
									SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(wolf->renderer, &r);
}

void			draw_map(t_wolf3d *wolf)
{
	t_color		color;
	t_position	position;

	position.y = -1;
	while (++position.y < wolf->map->height)
	{
		position.x = -1;
		while (++position.x < wolf->map->width)
		{
			if (wolf->map->map[position.y][position.x] == 1)
			{
				color.r = 0;
				color.g = 0;
				color.b = 128;
			}
			else
			{
				color.r = 0;
				color.g = 0;
				color.b = 100;
			}
			rect_draw(wolf, position, color);
		}
	}
}
