/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sdl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoss <mjoss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 22:42:22 by mjoss             #+#    #+#             */
/*   Updated: 2020/11/24 17:33:20 by mjoss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_wolf3d		init_sdl()
{
	t_wolf3d	wolf;

	SDL_Init(SDL_INIT_VIDEO);
    if ((wolf.win = SDL_CreateWindow("Wolf3D",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0)) == NULL)
		printf("Window create fail\n");
	else
		printf("Window create success\n");
	if (!(wolf.renderer = SDL_CreateRenderer(wolf.win, -1, 0)))
		printf("SDL create Renderer fail: %s\n", SDL_GetError());
	else
		printf("SDL create Renderer success\n");
	if ((wolf.sky_image = IMG_Load("textures/sky.png")) == NULL)
    	printf("imaged load fail\n");
    else
		printf("imaged load success\n");
	if ((wolf.sky_texture = SDL_CreateTextureFromSurface(wolf.renderer, wolf.sky_image)) == NULL)
		printf("SDL create texture from surface fail: %s\n", SDL_GetError());
	else
		printf("SDL create texture from surface success\n");
	load_textures(&wolf);
	if (Mix_OpenAudio(44100, AUDIO_F32SYS, 2, 2048) < 0)
    {
        //ft_putstr("error");
        exit(0);
    }
    wolf.sound.bgm = Mix_LoadMUS("sounds/1.wav");
    wolf.sound.sound_effect = Mix_LoadWAV("sounds/footstep1.wav");
	wolf.is_hit = 0;
	wolf.is_hit_down = 0;
	wolf.button.pressed = 0;
	return (wolf);
}