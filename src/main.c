/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoss <mjoss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 04:07:18 by mjoss             #+#    #+#             */
/*   Updated: 2020/11/17 22:56:08 by mjoss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include "libft.h"

void			fill_background(t_wolf3d *wolf)
{
	SDL_SetRenderDrawColor( wolf->renderer, 128, 128, 128, 255);
	SDL_RenderClear(wolf->renderer);
}

void			draw_sky(t_wolf3d *wolf)
{
	SDL_Rect	srect;
	SDL_Rect	drect;

	drect.x = SCREEN_WIDTH / 2;
	drect.y = 0;
	drect.w = SCREEN_WIDTH;
	drect.h = SCREEN_HEIGHT / 2;
	SDL_RenderCopy(wolf->renderer, wolf->sky_texture, NULL, &drect);
}

void			draw_floor(t_wolf3d *wolf)
{
	SDL_Rect	drect;

	drect.x = SCREEN_WIDTH / 2;
	drect.y = SCREEN_HEIGHT / 2;
	drect.w = SCREEN_WIDTH;
	drect.h = SCREEN_HEIGHT / 2;
	SDL_SetRenderDrawColor( wolf->renderer, 28, 128, 68, 255);
	SDL_RenderFillRect(wolf->renderer, &drect);
}

int             main(int argc, char **argv)
{
    t_wolf3d	wolf;
	float		player_x;
    float		player_y;
	float		player_dx;
	float		player_dy;
	float		player_alpha = 0;
	int			map_status;
	t_map		map;

	if ((map_status = parse_map(argv[1], &map)) == -1)
    {
		ft_putstr("wrong map\n");
        exit (0);
    }
	else if (map_status == 0)
	{
		ft_putstr("syscall err\n");
		exit (0);
	}
	player_dx = cos(player_alpha) * 5;
	player_dy = sin(player_alpha) * 5;
    wolf = init_sdl();
	player_x = map.player_position.x * map.width * map.height + 100;
	player_y = map.player_position.y * map.width * map.height + 100;
    wolf.is_running = 1;
	fill_background(&wolf);
	draw_sky(&wolf);
	draw_floor(&wolf);
	draw_map(map, &wolf);
	draw_rays(map, &wolf, player_x, player_y, player_alpha);
	draw_player(&wolf, player_x, player_y, player_dx, player_dy);
	SDL_RenderPresent(wolf.renderer);
    while (wolf.is_running)
    {
        while (SDL_PollEvent(&wolf.event))
        {
            if (wolf.event.type == SDL_QUIT || wolf.event.key.keysym.sym == SDLK_ESCAPE)
                wolf.is_running = 0;
            if (wolf.event.type == SDL_KEYDOWN)
            {
				if (wolf.event.key.keysym.sym == SDLK_p)
				{
					if (!(Mix_PlayingMusic()))
					{
						Mix_PlayMusic(wolf.sound.bgm, -1);		
					}
					else if(Mix_PausedMusic())
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
                if (wolf.event.key.keysym.sym == SDLK_LEFT)
				{
					player_alpha -= 0.1f;
					if (player_alpha < 0)
						player_alpha += 2 * M_PI;
					player_dx = cos(player_alpha) * 5;
					player_dy = sin(player_alpha) * 5;
				}
                else if (wolf.event.key.keysym.sym == SDLK_RIGHT)
				{
					player_alpha += 0.1f;
					if (player_alpha > 2 * M_PI)
						player_alpha -= 2 * M_PI;
					player_dx = cos(player_alpha) * 5;
					player_dy = sin(player_alpha) * 5;
				}
                else if (wolf.event.key.keysym.sym == SDLK_UP && wolf.is_hit == 0)
				{
                    player_x += player_dx;
					player_y += player_dy;
					Mix_PlayChannel(0, wolf.sound.sound_effect, 0);
				}
                else if (wolf.event.key.keysym.sym == SDLK_DOWN && wolf.is_hit == 0)
				{
					player_x -= player_dx;
                    player_y -= player_dy;
					Mix_PlayChannel(0, wolf.sound.sound_effect, 0);
				}
				wolf.is_hit = 0;
				fill_background(&wolf);
				draw_sky(&wolf);
				draw_floor(&wolf);
				draw_map(map, &wolf);
				draw_rays(map, &wolf, player_x, player_y, player_alpha);
				draw_player(&wolf, player_x, player_y, player_dx, player_dy);
				SDL_RenderPresent(wolf.renderer);
            }
    	}
	}
    destroy_sdl(wolf);
    return (0);
}

/*
	wolf.pixels[x + y * SCREEN_WIDTH] = 0xfff000;
	SDL_RenderClear(wolf.renderer);
	SDL_UpdateTexture(wolf.texture, NULL, wolf.pixels, SCREEN_WIDTH * sizeof(Uint32));
    SDL_RenderCopy(wolf.renderer, wolf.texture, NULL, NULL);
*/