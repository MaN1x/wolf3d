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

void            drawMap(int mapX, int mapY, int map[64], t_wolf3d wolf)
{
   int x, y, xo, yo;

   x = 0;
   y = 0;

    while (y < mapY)
    {
		x = 0;
        while (x < mapX)
        {
			if (map[y * mapX + x] == 1)
			{
				wolf.pixels[(x + y * 640) * 10] = 0xffffff;
			}
			else
			{
				wolf.pixels[(x + y * 640) * 10] = 0xff0000;
			}
            x++;
        }
        y++;
    }
}

int             main()
{
    t_wolf3d       wolf;
    t_color     color;
    int mapX = 8;
    int mapY = 8;
    int mapS = 64;

    int map[64] = {
        1, 1, 1, 1, 1, 1, 1, 1,
        1, 0, 1, 0, 0, 0, 0, 1,
        1, 0, 1, 0, 0, 0, 0, 1,
        1, 0, 1, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 1, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 1,
        1, 1, 1, 1, 1, 1, 1, 1
    };

    wolf = init_sdl();
    wolf.is_running = 1;
    color.r = 0;
    color.b = 0;
    color.g = 255;
    int x = 100;
    int y = 100;
	drawMap(mapX, mapY, map, wolf);
    while (wolf.is_running) {
        //put_pixel_sdl(wolf, x,y,color);
        wolf.pixels[x + y * 640] = 0xfff000;
        while (SDL_PollEvent(&wolf.event)) {
            if (wolf.event.type == SDL_QUIT || wolf.event.key.keysym.sym == SDLK_ESCAPE) {
                wolf.is_running = 0;
            }
            if (wolf.event.type == SDL_KEYDOWN)
            {
                if (wolf.event.key.keysym.sym == SDLK_UP)
                    y += 5;
                else if (wolf.event.key.keysym.sym == SDLK_DOWN)
                    y -= 5;
                else if (wolf.event.key.keysym.sym == SDLK_RIGHT)
                    x += 5;
                else if (wolf.event.key.keysym.sym == SDLK_LEFT)
                    x -= 5;
            }
    	}
        SDL_RenderClear(wolf.renderer);
        SDL_UpdateTexture(wolf.texture, NULL, wolf.pixels, 640 * sizeof(Uint32));
        SDL_RenderCopy(wolf.renderer, wolf.texture, NULL, NULL);
        SDL_RenderPresent(wolf.renderer);
	}
    destroy_sdl(wolf);
    return (0);
}