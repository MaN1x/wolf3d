/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_draw.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetrell <npetrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 20:38:39 by npetrell          #+#    #+#             */
/*   Updated: 2020/11/25 21:20:41 by npetrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			button_draw(t_wolf3d *wolf)
{
	SDL_Surface	*button_surface;
	SDL_Texture	*button_texture;

	wolf->button.color.r = 100;
	wolf->button.color.g = 100;
	wolf->button.color.b = 100;
	wolf->button.rect.w = SCREEN_HEIGHT / 20;
	wolf->button.rect.h = SCREEN_HEIGHT / 20;
	wolf->button.rect.x = 0;
	wolf->button.rect.y = SCREEN_HEIGHT - wolf->button.rect.h;
	if ((button_surface = IMG_Load("textures/settings.png")) == NULL)
	{
		ft_putstr("imaged load fail\n");
		exit(-1);
	}
	if ((button_texture = SDL_CreateTextureFromSurface(wolf->renderer,
													button_surface)) == NULL)
	{
		ft_putstr("SDL create texture from surface fail\n");
		exit(-1);
	}
	SDL_RenderCopy(wolf->renderer, button_texture, NULL, &wolf->button.rect);
	SDL_FreeSurface(button_surface);
	SDL_DestroyTexture(button_texture);
}
