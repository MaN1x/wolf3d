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

void            drawMap(int mapX, int mapY, int map[8][8], t_wolf3d *wolf)
{
   int x, y, xo, yo;

   x = 0;
   y = 0;
   t_color color;

    int mapGridSquareSize = 480/mapX;
    int mapXOffset = (640 - 480) / 2;
    int mapYOffset = (480 - 480) / 2;
    while (y < mapY)
    {
		x = 0;
        while (x < mapX)
        {
			if (map[x][y] == 1)
			{
				color.r = 0;
				color.g = 0;
				color.b = 255;
			}
			else
			{
				color.r = 255;
				color.g = 0;
				color.b = 0;	
			}
			SDL_Rect r;
			r.w = mapGridSquareSize / 2;
    		r.h = mapGridSquareSize / 2;
			r.x = (mapGridSquareSize / 2 * x) + mapXOffset;
			r.y = (mapGridSquareSize / 2 * y) + mapYOffset;

			SDL_SetRenderDrawColor( wolf->renderer, color.r, color.g, color.b, 255);
			SDL_RenderDrawRect(wolf->renderer, &r);
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

    wolf = init_sdl();
    wolf.is_running = 1;
    color.r = 0;
    color.b = 0;
    color.g = 255;
    int x = 100;
    int y = 100;
    while (wolf.is_running) {
        while (SDL_PollEvent(&wolf.event)) {
            if (wolf.event.type == SDL_QUIT || wolf.event.key.keysym.sym == SDLK_ESCAPE) {
                wolf.is_running = 0;
            }
            if (wolf.event.type == SDL_KEYDOWN)
            {
                if (wolf.event.key.keysym.sym == SDLK_UP)
                    y += 1;
                else if (wolf.event.key.keysym.sym == SDLK_DOWN)
                    y -= 1;
                else if (wolf.event.key.keysym.sym == SDLK_RIGHT)
                    x += 1;
                else if (wolf.event.key.keysym.sym == SDLK_LEFT)
                    x -= 1;
            }
    	}
        wolf.pixels[x + y * 640] = 0xfff000;
        SDL_UpdateTexture(wolf.texture, NULL, wolf.pixels, 640 * sizeof(Uint32));
        SDL_RenderCopy(wolf.renderer, wolf.texture, NULL, NULL);
		drawMap(mapX, mapY, map, &wolf);
        SDL_RenderPresent(wolf.renderer);
		//SDL_RenderClear(wolf.renderer);
	}
    destroy_sdl(wolf);
    return (0);
}