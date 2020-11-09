/*
 * Filename: /Users/Student/mandelbrot/main.c
 * Path: /Users/Student/mandelbrot
 * Created Date: Tuesday, May 12th 2020, 9:35:08 pm
 * Author: Student
 * 
 * Copyright (c) 2020 Your Company
 */

#include "wolf3d.h"
#include <stdio.h>

void			draw_ray(int x, int y, )
{
	
}

void            draw_map(int mapX, int mapY, int map[8][8], t_wolf3d *wolf)
{
   int x, y, xo, yo;

	x = 0;
	y = 0;
	SDL_Rect r;
	t_color color;

    int mapGridSquareSize = 480 / mapX;
    int mapXOffset = (640 - 480) / 2;
    int mapYOffset = (480 - 480) / 2;
    while (y < mapY)
    {
		x = 0;
        while (x < mapX)
        {
			color.g = 0;
			if (map[x][y] == 1)
			{
				color.r = 255;
				color.b = 0;
			}
			else
			{
				color.r = 0;
				color.b = 255;	
			}
			r.w = mapGridSquareSize;
    		r.h = mapGridSquareSize;
			r.x = (mapGridSquareSize * x) + mapXOffset;
			r.y = (mapGridSquareSize * y) + mapYOffset;

			SDL_SetRenderDrawColor( wolf->renderer, color.r, color.g, color.b, 255);
			SDL_RenderDrawRect(wolf->renderer, &r);
            x++;
        }
        y++;
    }
}

void            draw_player(t_wolf3d *wolf, int x, int y, int dx, int dy)
{
    t_color     color;
    SDL_Rect    r;

    r.x = x;
    r.y = y;
    r.w = 5;
    r.h = 5;
    color.r = 255;
    color.b = 255;
    color.g = 255;
    SDL_SetRenderDrawColor( wolf->renderer, color.r, color.g, color.b, 255);
    SDL_RenderFillRect(wolf->renderer, &r);
	//wolf->pixels[x + y * 640] = 0xffffff;
	//SDL_RenderClear(wolf->renderer);
	//SDL_UpdateTexture(wolf->texture, NULL, wolf->pixels, 640 * sizeof(Uint32));

	SDL_SetRenderDrawColor(wolf->renderer, color.r, color.g, color.b, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawLine(wolf->renderer, x, y, x + dx * 10, y + dy * 10);
}

void			fill_background(t_wolf3d *wolf)
{
	SDL_SetRenderDrawColor( wolf->renderer, 128, 128, 128, 255);
	SDL_RenderClear(wolf->renderer);
}


int             main()
{
    t_wolf3d	wolf;
    int			mapX = 8;
    int			mapY = 8;
    int			mapS = 64;
	float		player_x = 100;
    float		player_y = 100;
	float		player_dx;
	float		player_dy;
	float		player_alpha = 0;

    int map[8][8] = {
        {1, 1, 1, 1, 1, 1, 1, 1}, 
        {1, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 0, 1, 0, 0, 0, 1},
        {1, 1, 1, 0, 0, 0, 0, 1},
        {1, 1, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1}
    };
	player_dx = cos(player_alpha) * 10;
	player_dy = sin(player_alpha) * 10;
    wolf = init_sdl();
    wolf.is_running = 1;
    while (wolf.is_running) {
        while (SDL_PollEvent(&wolf.event)) {
            if (wolf.event.type == SDL_QUIT || wolf.event.key.keysym.sym == SDLK_ESCAPE) {
                wolf.is_running = 0;
            }
            if (wolf.event.type == SDL_KEYDOWN)
            {
                if (wolf.event.key.keysym.sym == SDLK_UP)
				{
					player_alpha -= 0.1f;
					if (player_alpha < 0)
						player_alpha += 2 * M_PI;
					player_dx = cos(player_alpha) * 10;
					player_dy = sin(player_alpha) * 10;
				}
                else if (wolf.event.key.keysym.sym == SDLK_DOWN)
				{
					player_alpha += 0.1f;
					if (player_alpha > 2 * M_PI)
						player_alpha -= 2 * M_PI;
					player_dx = cos(player_alpha) * 10;
					player_dy = sin(player_alpha) * 10;
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
		draw_player(&wolf, player_x, player_y, player_dx, player_dy);
		draw_map(mapX, mapY, map, &wolf);
        SDL_RenderPresent(wolf.renderer);
	}
    destroy_sdl(wolf);
    return (0);
}

/*
	wolf.pixels[x + y * 640] = 0xfff000;
	SDL_RenderClear(wolf.renderer);
	SDL_UpdateTexture(wolf.texture, NULL, wolf.pixels, 640 * sizeof(Uint32));
    SDL_RenderCopy(wolf.renderer, wolf.texture, NULL, NULL);
*/