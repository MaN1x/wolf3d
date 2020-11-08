/*
 * Filename: /Users/Student/mandelbrot/destroy_sdl.c
 * Path: /Users/Student/mandelbrot
 * Created Date: Tuesday, May 12th 2020, 10:59:35 pm
 * Author: Student
 * 
 * Copyright (c) 2020 Your Company
 */

#include "wolf3d.h"

void	destroy_sdl(t_wolf3d wolf)
{
	SDL_DestroyTexture(wolf.texture);
    SDL_DestroyRenderer(wolf.renderer);
    SDL_DestroyWindow(wolf.win);
    SDL_Quit();
}