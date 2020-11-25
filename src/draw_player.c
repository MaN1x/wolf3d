/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetrell <npetrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 21:44:43 by npetrell          #+#    #+#             */
/*   Updated: 2020/11/25 21:58:28 by npetrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			draw_player(t_wolf3d *wolf, t_pos first, t_pos second)
{
	t_color		color;
	SDL_Rect	r;

	r.w = (SCREEN_WIDTH * SIZE_MAP) / wolf->map->width;
	r.h = (SCREEN_HEIGHT * SIZE_MAP) / wolf->map->height;
	r.x = first.x / wolf->factor * r.w;
	r.y = first.y / wolf->factor * r.h;
	r.w = 3;
	r.h = 3;
	color.r = 255;
	color.b = 255;
	color.g = 255;
	SDL_SetRenderDrawColor(wolf->renderer, color.r, color.g, color.b, 255);
	SDL_RenderFillRect(wolf->renderer, &r);
	SDL_SetRenderDrawColor(wolf->renderer, color.r, color.g, color.b,
														SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLine(wolf->renderer, r.x, r.y, r.x + second.x * 5,
														r.y + second.y * 5);
}
