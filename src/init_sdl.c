/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sdl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoss <mjoss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 22:42:22 by mjoss             #+#    #+#             */
/*   Updated: 2020/11/17 22:42:22 by mjoss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_wolf3d		init_sdl()
{
	t_wolf3d	wolf;

	SDL_Init(SDL_INIT_VIDEO);
    if ((wolf.win = SDL_CreateWindow("SDL2 Pixel Drawing",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0)) == NULL)
		printf("Window create fail\n");
	else
		printf("Window create success\n");
	if (!(wolf.renderer = SDL_CreateRenderer(wolf.win, -1, 0)))
		printf("SDL create Renderer fail: %s\n", SDL_GetError());
	else
		printf("SDL create Renderer success\n");
	if ((wolf.sky_image = IMG_Load("sky.png")) == NULL)
    	printf("imaged load fail\n");
    else
		printf("imaged load success\n");
	if ((wolf.sky_texture = SDL_CreateTextureFromSurface(wolf.renderer, wolf.sky_image)) == NULL)
		printf("SDL create texture from surface fail: %s\n", SDL_GetError());
	else
		printf("SDL create texture from surface success\n");
    if ((wolf.image = IMG_Load("barash.jpg")) == NULL)
    	printf("imaged load fail\n");
    else
		printf("imaged load success\n");
	if ((wolf.texture = SDL_CreateTextureFromSurface(wolf.renderer, wolf.image)) == NULL)
		printf("SDL create texture from surface fail: %s\n", SDL_GetError());
	else
		printf("SDL create texture from surface success\n");
	wolf.is_hit = 0;
	return (wolf);
}