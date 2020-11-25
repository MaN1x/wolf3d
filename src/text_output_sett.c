/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text_output_sett.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetrell <npetrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 20:40:54 by npetrell          #+#    #+#             */
/*   Updated: 2020/11/25 21:22:23 by npetrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void				first_string(t_wolf3d *wolf, SDL_Renderer **renderer,
															SDL_Color color)
{
	SDL_Surface		*surface;
	SDL_Texture		*texture;

	surface = TTF_RenderText_Solid(wolf->button.txt.font,
"Change direction moving key_buttons              LEFT/RIGHT   |    A/D",
	color);
	texture = SDL_CreateTextureFromSurface(*renderer, surface);
	wolf->button.txt.rect.h = 32;
	wolf->button.txt.rect.w = 450;
	wolf->button.txt.rect.x = 25;
	wolf->button.txt.rect.y = 0;
	SDL_RenderCopy(*renderer, texture, NULL, &wolf->button.txt.rect);
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
}

void				second_string(t_wolf3d *wolf, SDL_Renderer **renderer,
															SDL_Color color)
{
	SDL_Surface		*surface;
	SDL_Texture		*texture;

	surface = TTF_RenderText_Solid(wolf->button.txt.font,
		"Change movement key_buttons         UP/DOWN    |    W/S", color);
	texture = SDL_CreateTextureFromSurface(*renderer, surface);
	wolf->button.txt.rect.h = 32;
	wolf->button.txt.rect.w = 450;
	wolf->button.txt.rect.x = 25;
	wolf->button.txt.rect.y = 42;
	SDL_RenderCopy(*renderer, texture, NULL, &wolf->button.txt.rect);
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
}

void				third_string(t_wolf3d *wolf, SDL_Renderer **renderer,
															SDL_Color color)
{
	SDL_Surface		*surface;
	SDL_Texture		*texture;

	surface = TTF_RenderText_Solid(wolf->button.txt.font,
		"Play/Stop/Pause music        P/S/Q", color);
	texture = SDL_CreateTextureFromSurface(*renderer, surface);
	wolf->button.txt.rect.h = 32;
	wolf->button.txt.rect.w = 450;
	wolf->button.txt.rect.x = 25;
	wolf->button.txt.rect.y = 84;
	SDL_RenderCopy(*renderer, texture, NULL, &wolf->button.txt.rect);
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
}

void				fourth_string(t_wolf3d *wolf, SDL_Renderer **renderer,
															SDL_Color color)
{
	SDL_Surface		*surface;
	SDL_Texture		*texture;

	surface = TTF_RenderText_Solid(wolf->button.txt.font,
		"Exit from program       Esc", color);
	texture = SDL_CreateTextureFromSurface(*renderer, surface);
	wolf->button.txt.rect.h = 32;
	wolf->button.txt.rect.w = 450;
	wolf->button.txt.rect.x = 25;
	wolf->button.txt.rect.y = 126;
	SDL_RenderCopy(*renderer, texture, NULL, &wolf->button.txt.rect);
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
}

void				text_output(t_wolf3d *wolf)
{
	SDL_Renderer	*renderer;
	SDL_Color		color;

	TTF_Init();
	if (!(wolf->button.txt.font = TTF_OpenFont("src/game.ttf", 40)))
	{
		ft_putstr("problem loading font");
		exit(0);
	}
	if (!(renderer = SDL_CreateRenderer(wolf->button.win, -1, 0)))
	{
		ft_putstr("SDL create Renderer fail %s\n");
		exit(0);
	}
	color.r = 200;
	color.g = 12;
	color.b = 12;
	first_string(wolf, &renderer, color);
	second_string(wolf, &renderer, color);
	third_string(wolf, &renderer, color);
	fourth_string(wolf, &renderer, color);
	SDL_RenderPresent(renderer);
	TTF_CloseFont(wolf->button.txt.font);
}
