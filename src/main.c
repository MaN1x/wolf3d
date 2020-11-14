/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoss <mjoss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 04:07:18 by mjoss             #+#    #+#             */
/*   Updated: 2020/11/13 04:27:24 by mjoss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include "libft.h"
#include <stdio.h>

void			fill_background(t_wolf3d *wolf)
{
	SDL_SetRenderDrawColor( wolf->renderer, 128, 128, 128, 255);
	SDL_RenderClear(wolf->renderer);
}


int             main(int argc, char **argv)
{
    t_wolf3d	wolf;
    int			mapX = 8;
    int			mapY = 8;
    int			mapS = 64;
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
	player_x = map.player_position.x * map.width * map.height;
	player_y = map.player_position.y * map.width * map.height;
    wolf.is_running = 1;
	//fill_background(&wolf);
	draw_map(map, &wolf);
	draw_rays(map, &wolf, player_x, player_y, player_alpha);
	draw_player(&wolf, player_x, player_y, player_dx, player_dy);
    wolf.texr.x = player_x; wolf.texr.y = player_y; wolf.texr.w = 600 / 4; wolf.texr.h = 600 /4;
    while (wolf.is_running)
    {
		//SDL_RenderClear (wolf.renderer);

		 //SDL_RenderClear (wolf.renderer);
        while (SDL_PollEvent(&wolf.event))
        {
            if (wolf.event.type == SDL_QUIT || wolf.event.key.keysym.sym == SDLK_ESCAPE)
                wolf.is_running = 0;
            if (wolf.event.type == SDL_KEYDOWN)
            {
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
                else if (wolf.event.key.keysym.sym == SDLK_UP)
				{
                    player_x += player_dx;
					player_y += player_dy;
				}
                else if (wolf.event.key.keysym.sym == SDLK_DOWN)
				{
					player_x -= player_dx;
                    player_y -= player_dy;
				}
				//fill_background(&wolf);
				draw_map(map, &wolf);
				draw_rays(map, &wolf, player_x, player_y, player_alpha);
				draw_player(&wolf, player_x, player_y, player_dx, player_dy);
            }
    	}
		SDL_RenderCopy(wolf.renderer, wolf.texture, NULL, &wolf.texr);
		SDL_RenderPresent(wolf.renderer);
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