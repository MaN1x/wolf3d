/*
 * Filename: /Users/Student/mandelbrot/main.c
 * Path: /Users/Student/mandelbrot
 * Created Date: Tuesday, May 12th 2020, 9:35:08 pm
 * Author: Student
 * 
 * Copyright (c) 2020 Your Company
 */

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
    while (wolf.is_running) {
        while (SDL_PollEvent(&wolf.event)) {
            if (wolf.event.type == SDL_QUIT || wolf.event.key.keysym.sym == SDLK_ESCAPE) {
                wolf.is_running = 0;
            }
            if (wolf.event.type == SDL_KEYDOWN)
            {
                if (wolf.event.key.keysym.sym == SDLK_DOWN)
				{
					player_alpha -= 0.1;
					if (player_alpha < 0)
						player_alpha += 2 * M_PI;
					player_dx = cos(player_alpha) * 5;
					player_dy = sin(player_alpha) * 5;
				}
                else if (wolf.event.key.keysym.sym == SDLK_UP)
				{
					player_alpha += 0.1;
					if (player_alpha > 2 * M_PI)
						player_alpha -= 2 * M_PI;
					player_dx = cos(player_alpha) * 5;
					player_dy = sin(player_alpha) * 5;
				}
                else if (wolf.event.key.keysym.sym == SDLK_RIGHT)
				{
                    player_x += player_dx;
					player_y += player_dy;
				}
                else if (wolf.event.key.keysym.sym == SDLK_LEFT)
				{
					player_x -= player_dx;
                    player_y -= player_dy;
				}
            }
    	}
		fill_background(&wolf);
		draw_map(map, &wolf);
    	//SDL_RenderCopy(wolf.renderer, wolf.texture, NULL, NULL);
        draw_ray(map, &wolf, player_x, player_y, player_alpha);
        draw_player(&wolf, player_x, player_y, player_dx, player_dy);
		//SDL_RenderClear(wolf.renderer);
		//SDL_UpdateTexture(wolf.texture, NULL, wolf.pixels, SCREEN_WIDTH * sizeof(Uint32));
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