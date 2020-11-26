/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoss <mjoss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 16:23:52 by mjoss             #+#    #+#             */
/*   Updated: 2020/11/26 18:32:16 by mjoss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	music_control(t_wolf3d wolf)
{
	if (wolf.event.key.keysym.sym == SDLK_p)
	{
		if (!(Mix_PlayingMusic()))
		{
			Mix_PlayMusic(wolf.sound.bgm, -1);
		}
		else if (Mix_PausedMusic())
		{
			Mix_ResumeMusic();
		}
		else
		{
			Mix_PausedMusic();
		}
	}
	else if (wolf.event.key.keysym.sym == SDLK_q)
	{
		Mix_PauseMusic();
	}
	else if (wolf.event.key.keysym.sym == SDLK_s)
	{
		Mix_HaltMusic();
	}
}

void	move_vertical(t_wolf3d wolf, t_player *player, float *dx, float *dy)
{
	if (wolf.event.key.keysym.sym == SDLK_LEFT ||
		wolf.event.key.keysym.sym == SDLK_a)
	{
		player->angle -= 0.1f;
		if (player->angle < 0)
			player->angle += 2 * M_PI;
		*dx = cos(player->angle) * 5;
		*dy = sin(player->angle) * 5;
	}
	else if (wolf.event.key.keysym.sym == SDLK_RIGHT ||
				wolf.event.key.keysym.sym == SDLK_d)
	{
		player->angle += 0.1f;
		if (player->angle > 2 * M_PI)
			player->angle -= 2 * M_PI;
		*dx = cos(player->angle) * 5;
		*dy = sin(player->angle) * 5;
	}
}

void	move_horisontal(t_wolf3d wolf, t_player *player, float *dx, float *dy)
{
	if ((wolf.event.key.keysym.sym == SDLK_UP ||
			wolf.event.key.keysym.sym == SDLK_w) && wolf.is_hit == 0)
	{
		player->x += *dx;
		player->y += *dy;
		Mix_PlayChannel(0, wolf.sound.sound_effect, 0);
	}
	else if ((wolf.event.key.keysym.sym == SDLK_DOWN ||
				wolf.event.key.keysym.sym == SDLK_s) && wolf.is_hit_down == 0)
	{
		player->x -= *dx;
		player->y -= *dy;
		Mix_PlayChannel(0, wolf.sound.sound_effect, 0);
	}
}

void	movement(t_wolf3d wolf, t_player *player, float *player_dx,
														float *player_dy)
{
	move_vertical(wolf, player, player_dx, player_dy);
	move_horisontal(wolf, player, player_dx, player_dy);
}
