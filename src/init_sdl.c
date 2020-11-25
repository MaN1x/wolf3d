/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sdl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetrell <npetrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 22:42:22 by mjoss             #+#    #+#             */
/*   Updated: 2020/11/25 22:13:07 by npetrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			ft_error(char *str)
{
	ft_putstr(str);
	exit(-1);
}

void			init(t_wolf3d *wolf)
{
	wolf->sound.bgm = Mix_LoadMUS("sounds/1.wav");
	wolf->sound.sound_effect = Mix_LoadWAV("sounds/footstep1.wav");
	wolf->is_hit = 0;
	wolf->is_hit_down = 0;
	wolf->button.pressed = 0;
}

t_wolf3d		init_sdl(void)
{
	t_wolf3d	wolf;

	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
	if ((wolf.win = SDL_CreateWindow("Wolf3D",
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
						SCREEN_WIDTH, SCREEN_HEIGHT, 0)) == NULL)
		ft_error("Window create fail\n");
	if (!(wolf.renderer = SDL_CreateRenderer(wolf.win, -1, 0)))
		ft_error("SDL create Renderer fail\n");
	if ((wolf.sky_image = IMG_Load("textures/sky.png")) == NULL)
		ft_error("imaged load fail\n");
	if ((wolf.sky_texture = SDL_CreateTextureFromSurface(wolf.renderer,
													wolf.sky_image)) == NULL)
		ft_error("SDL create texture from surface fail\n");
	load_textures(&wolf);
	if (Mix_OpenAudio(44100, AUDIO_F32SYS, 2, 2048) < 0)
		ft_error("audio load fail\n");
	init(&wolf);
	return (wolf);
}
