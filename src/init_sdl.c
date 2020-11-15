/*
 * Filename: /Users/Student/mandelbrot/init_sdl.c
 * Path: /Users/Student/mandelbrot
 * Created Date: Tuesday, May 12th 2020, 10:42:02 pm
 * Author: Student
 * 
 * Copyright (c) 2020 Your Company
 */

#include "wolf3d.h"
#include <stdio.h>

t_wolf3d		init_sdl()
{
	t_wolf3d	wolf;

	SDL_Init(SDL_INIT_VIDEO);
    wolf.win = SDL_CreateWindow("SDL2 Pixel Drawing",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	wolf.renderer = SDL_CreateRenderer(wolf.win, -1, 0);
   	wolf.texture = SDL_CreateTexture(wolf.renderer,
        SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, SCREEN_WIDTH, SCREEN_HEIGHT);
    wolf.pixels = malloc(sizeof(Uint32) * SCREEN_WIDTH * SCREEN_HEIGHT);//new Uint32[SCREEN_WIDTH * 480];
    memset(wolf.pixels, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));
/*
    if ((wolf.screen = SDL_GetWindowSurface(wolf.win)) == NULL)
		printf("Error get window surface\n%s\n", (char*)SDL_GetError());
	else
		printf("Success get window surface\n");
*/
    if ((wolf.image = IMG_Load("barash.jpg")) == NULL)
    	printf("Error load img\n");
    else
    	printf("Success load img\n");
/*
    if ((SDL_BlitSurface(wolf.image, NULL, wolf.screen, NULL)) < 0)
		printf("Error blit surface\n");
	else
		printf("Success blit surface\n");
    if ((SDL_UpdateWindowSurface(wolf.win)) == 0)
		printf("Success update window surface\n");
    else
		printf("Error update window surface\n");
*/
	if ((wolf.texture = SDL_CreateTextureFromSurface(wolf.renderer, wolf.image)) == NULL)
		printf("Error create texture from surface\n");
	else
		printf("Success create texture from surface\n");
	return (wolf);
}