/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_sdl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetrell <npetrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 20:47:32 by npetrell          #+#    #+#             */
/*   Updated: 2020/11/25 20:48:44 by npetrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	destroy_sdl(t_wolf3d wolf)
{
	Mix_FreeChunk(wolf.sound.sound_effect);
	Mix_FreeMusic(wolf.sound.bgm);
	wolf.sound.bgm = NULL;
	wolf.sound.sound_effect = NULL;
	SDL_FreeSurface(wolf.sky_image);
	SDL_DestroyTexture(wolf.sky_texture);
	SDL_DestroyRenderer(wolf.renderer);
	SDL_DestroyWindow(wolf.button.win);
	SDL_DestroyWindow(wolf.win);
	SDL_Quit();
}
