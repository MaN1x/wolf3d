/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoss <mjoss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 17:01:55 by mjoss             #+#    #+#             */
/*   Updated: 2020/11/26 18:33:09 by mjoss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	fill_background(t_wolf3d *wolf)
{
	SDL_SetRenderDrawColor(wolf->renderer, 128, 128, 128, 255);
	SDL_RenderClear(wolf->renderer);
}

void	draw_sky(t_wolf3d *wolf)
{
	SDL_Rect	drect;

	drect.x = 0;
	drect.y = 0;
	drect.w = SCREEN_WIDTH;
	drect.h = SCREEN_HEIGHT / 2;
	SDL_RenderCopy(wolf->renderer, wolf->sky_texture, NULL, &drect);
}

void	draw_floor(t_wolf3d *wolf)
{
	SDL_Rect	drect;

	drect.x = 0;
	drect.y = SCREEN_HEIGHT / 2;
	drect.w = SCREEN_WIDTH;
	drect.h = SCREEN_HEIGHT / 2;
	SDL_SetRenderDrawColor(wolf->renderer, 192, 192, 192, 192);
	SDL_RenderFillRect(wolf->renderer, &drect);
}

void	draw_all(t_wolf3d *wolf, t_player player, float dx, float dy)
{
	t_pos first;
	t_pos second;

	first.x = player.x;
	first.y = player.y;
	second.x = dx;
	second.y = dy;
	fill_background(wolf);
	draw_sky(wolf);
	draw_floor(wolf);
	draw_rays(wolf, player);
	draw_map(wolf);
	draw_player(wolf, first, second);
	logo_draw(wolf);
	button_draw(wolf);
}
