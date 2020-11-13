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

	SDL_Init(SDL_INIT_AUDIO);
    wolf.win = SDL_CreateWindow("SDL2 Pixel Drawing",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if (Mix_OpenAudio(44100, AUDIO_F32SYS, 2, 2048) < 0)
    {
        //ft_putstr("error");
        exit(0);
    }
    wolf.sound.bgm = Mix_LoadMUS("1.wav");
    wolf.sound.sound_effect = Mix_LoadWAV("Cuica-1.wav");
	return (wolf);
}