/*
 * Filename: /Users/Student/mandelbrot/init_sdl.c
 * Path: /Users/Student/mandelbrot
 * Created Date: Tuesday, May 12th 2020, 10:42:02 pm
 * Author: Student
 * 
 * Copyright (c) 2020 Your Company
 */

#include "wolf3d.h"

t_wolf3d		init_sdl()
{
	t_wolf3d	wolf;

	SDL_Init(SDL_INIT_VIDEO);
    wolf.win = SDL_CreateWindow("SDL2 Pixel Drawing",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);
	wolf.renderer = SDL_CreateRenderer(wolf.win, -1, 0);
   // SDL_SetRenderDrawColor(wolf.renderer, 255, 255, 255, 255);
    //SDL_RenderClear(wolf.renderer); // fill the scene with white
   	wolf.texture = SDL_CreateTexture(wolf.renderer,
        SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, 640, 480);
    wolf.pixels = malloc(sizeof(Uint32) * 640 * 480);//new Uint32[640 * 480];
    memset(wolf.pixels, 0, 640 * 480 * sizeof(Uint32));
	return (wolf);
}