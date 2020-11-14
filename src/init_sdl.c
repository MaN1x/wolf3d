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

	SDL_Init(SDL_INIT_EVERYTHING);
    wolf.win = SDL_CreateWindow("SDL2 Pixel Drawing",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	wolf.renderer = SDL_CreateRenderer(wolf.win, -1, 0);
    //wolf.screen = SDL_GetWindowSurface(wolf.win);
   // SDL_SetRenderDrawColor(wolf.renderer, 255, 255, 255, 255);
    //SDL_RenderClear(wolf.renderer); // fill the scene with white
   //	wolf.texture = SDL_CreateTexture(wolf.renderer,
   //     SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, SCREEN_WIDTH, SCREEN_HEIGHT);
   // wolf.pixels = malloc(sizeof(Uint32) * SCREEN_WIDTH * SCREEN_HEIGHT);//new Uint32[SCREEN_WIDTH * 480];
  //  memset(wolf.pixels, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));
   //wolf.image = IMG_Load("wall.png");
    //SDL_BlitSurface(wolf.image, NULL, wolf.screen, NULL); // blit it to the screen
    //SDL_FreeSurface(wolf.image);
    //SDL_UpdateWindowSurface(wolf.win);
    //SDL_Delay(2000);
	//wolf.texture = SDL_CreateTextureFromSurface(wolf.renderer, wolf.image);
    int w, h;
    wolf.texture = IMG_LoadTexture(wolf.renderer, "wall.png");
	SDL_QueryTexture(wolf.texture, NULL, NULL, &w, &h);
	return (wolf);
}