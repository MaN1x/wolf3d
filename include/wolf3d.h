/*
 * Filename: /Users/Student/mandelbrot/include/wolf3d.h
 * Path: /Users/Student/mandelbrot/include
 * Created Date: Tuesday, May 12th 2020, 10:09:25 pm
 * Author: Student
 * 
 * Copyright (c) 2020 Your Company
 */

#ifndef WOLF3D_H
# define WOLF3D_H
# define SCREEN_HEIGHT	720
# define SCREEN_WIDTH	1024
# include "SDL2/SDL.h"
# include "SDL2/SDL_image.h"
# include <unistd.h>
# include <math.h>

typedef struct			s_wolf3d
{
	SDL_Window			*win;
	SDL_Event			event;
	SDL_Renderer		*renderer;

	SDL_Surface			*image;
	SDL_Texture			*texture;
	Uint32				*pixels;
	int					is_running;
}						t_wolf3d;

typedef struct			s_color
{
	unsigned char		r;
	unsigned char		g;
	unsigned char		b;
}						t_color;

t_wolf3d				init_sdl();
void    				put_pixel_sdl(t_wolf3d wolf, int x, int y, t_color color);
void					destroy_sdl(t_wolf3d wolf);

#endif