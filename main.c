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

int             main()
{
    t_wolf3d       wolf;
    t_color     color;
    t_cl        cl;

    wolf = init_sdl();
    wolf.is_running = 1;
    color.r = 0;
    color.b = 0;
    color.g = 255;
    put_pixel_sdl(wolf, 100,100,color);
    while (wolf.is_running) {
        SDL_UpdateTexture(wolf.texture, NULL, wolf.pixels, 640 * sizeof(Uint32));
        while (SDL_PollEvent(&wolf.event)) {
            if (wolf.event.type == SDL_QUIT || wolf.event.key.keysym.sym == SDLK_ESCAPE) {
                wolf.is_running = 0;
       		}
    	}

    //put_pixel_sdl(wolf, 100, 100, color);
        SDL_RenderClear(wolf.renderer);
        SDL_RenderCopy(wolf.renderer, wolf.texture, NULL, NULL);
        SDL_RenderPresent(wolf.renderer);
	}
    clFinish(cl.commands);
	clReleaseMemObject(cl.data);
    clReleaseCommandQueue(cl.commands);
    clReleaseContext(cl.context);
    destroy_sdl(wolf);
    return (0);
}