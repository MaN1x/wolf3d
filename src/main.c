/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoss <mjoss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 04:07:18 by mjoss             #+#    #+#             */
/*   Updated: 2020/11/24 04:22:46 by mjoss            ###   ########.fr       */
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
	SDL_Rect	drect;

	drect.x = 0;
	drect.y = 0;
	drect.w = SCREEN_WIDTH;
	drect.h = SCREEN_HEIGHT / 2;
	SDL_RenderCopy(wolf->renderer, wolf->sky_texture, NULL, &drect);
}

void			draw_floor(t_wolf3d *wolf)
{
	SDL_Rect	drect;

	drect.x = 0;
	drect.y = SCREEN_HEIGHT / 2;
	drect.w = SCREEN_WIDTH;
	drect.h = SCREEN_HEIGHT / 2;
	SDL_SetRenderDrawColor( wolf->renderer, 192, 192, 192, 192);
	SDL_RenderFillRect(wolf->renderer, &drect);
}

int             main(int argc, char **argv)
{
    t_wolf3d	wolf;
    t_player	player;
	float		player_dx;
	float		player_dy;
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
    wolf = init_sdl();
	wolf.factor = (SCREEN_WIDTH / 16);
	player.x = map.player_position.x * wolf.factor;
	player.y = map.player_position.y * wolf.factor;
	player.angle = 3.915858;
	player_dx = cos(player.angle) * 5;
	player_dy = sin(player.angle) * 5;
	wolf.map = &map;

    wolf.is_running = 1;
	fill_background(&wolf);
	draw_sky(&wolf);
	draw_floor(&wolf);
	draw_rays(map, &wolf, player);
	draw_map(map, &wolf);
	draw_player(&wolf, player.x, (int)player.y, (int)player_dx, player_dy);
	logo_draw(&wolf);
	button_draw(&wolf);
	SDL_RenderPresent(wolf.renderer);
    while (wolf.is_running)
    {
        while (SDL_PollEvent(&wolf.event))
        {
            if (wolf.event.type == SDL_QUIT || (wolf.event.type == SDL_KEYDOWN && wolf.event.key.keysym.sym == SDLK_ESCAPE))
                wolf.is_running = 0;
			if (wolf.event.type == SDL_WINDOWEVENT &&
                   wolf.event.window.event == SDL_WINDOWEVENT_CLOSE)
			{
				wolf.button.pressed = 0;
				SDL_HideWindow(wolf.button.win);
				SDL_DestroyWindow(wolf.button.win);
			}
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
                if (wolf.event.key.keysym.sym == SDLK_LEFT || wolf.event.key.keysym.sym == SDLK_a)
				{
					player.angle -= 0.1f;
					if (player.angle < 0)
						player.angle += 2 * M_PI;
					player_dx = cos(player.angle) * 5;
					player_dy = sin(player.angle) * 5;
				}
                else if (wolf.event.key.keysym.sym == SDLK_RIGHT || wolf.event.key.keysym.sym == SDLK_d)
				{
					player.angle += 0.1f;
					if (player.angle > 2 * M_PI)
						player.angle -= 2 * M_PI;
					player_dx = cos(player.angle) * 5;
					player_dy = sin(player.angle) * 5;
				}
                else if ((wolf.event.key.keysym.sym == SDLK_UP || wolf.event.key.keysym.sym == SDLK_w) && wolf.is_hit == 0)
				{
                    player.x += player_dx;
					player.y += player_dy;
					Mix_PlayChannel(0, wolf.sound.sound_effect, 0);
				}
                else if ((wolf.event.key.keysym.sym == SDLK_DOWN || wolf.event.key.keysym.sym == SDLK_s) && wolf.is_hit_down == 0)
				{
					player.x -= player_dx;
                    player.y -= player_dy;
					Mix_PlayChannel(0, wolf.sound.sound_effect, 0);
				}
            }
			wolf.is_hit = 0;
			wolf.is_hit_down = 0;
			fill_background(&wolf);
			draw_sky(&wolf);
			draw_floor(&wolf);
			draw_rays(map, &wolf, player);
			draw_map(map, &wolf);
			draw_player(&wolf, player.x, player.y, player_dx, player_dy);
			logo_draw(&wolf);
			button_draw(&wolf);
			button_init(&wolf);
			SDL_RenderPresent(wolf.renderer);
    	}
	}
	free_wall(wolf.textures);
    destroy_sdl(wolf);
    return (0);
}
