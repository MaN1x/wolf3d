/*
 * Filename: /Users/Student/mandelbrot/main.c
 * Path: /Users/Student/mandelbrot
 * Created Date: Tuesday, May 12th 2020, 9:35:08 pm
 * Author: Student
 * 
 * Copyright (c) 2020 Your Company
 */

#include "wolf3d.h"

int             main(int argc, char **argv)
{
    t_wolf3d	wolf;
	
    wolf = init_sdl();
    wolf.is_running = 1;
    while (wolf.is_running) {
        while (SDL_PollEvent(&wolf.event)) {
            if (wolf.event.type == SDL_QUIT || wolf.event.key.keysym.sym == SDLK_ESCAPE) {
                wolf.is_running = 0;
            }
            if (wolf.event.type == SDL_KEYDOWN)
            {
                if (wolf.event.key.keysym.sym == SDLK_p)
				{
					if (!(Mix_PlayingMusic()))
					{
						Mix_PlayMusic(wolf.sound.bgm, -1);		
					}
					else if(Mix_PausedMusic())
					{
						Mix_ResumeMusic();
					}
					else
					{
						Mix_PausedMusic();						
					}
				}
				else if (wolf.event.key.keysym.sym == SDLK_q)
				{
					Mix_PauseMusic();
				}
                else if (wolf.event.key.keysym.sym == SDLK_s)
				{
					Mix_HaltMusic();
				}
				else if (wolf.event.key.keysym.sym == SDLK_1)
				{
					Mix_PlayChannel(-1, wolf.sound.sound_effect, 0);
				}
            }
    	}
		
	}
    destroy_sdl(wolf);
    return (0);
}
