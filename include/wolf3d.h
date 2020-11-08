/*
 * Filename: /Users/Student/mandelbrot/include/wolf3d.h
 * Path: /Users/Student/mandelbrot/include
 * Created Date: Tuesday, May 12th 2020, 10:09:25 pm
 * Author: Student
 * 
 * Copyright (c) 2020 Your Company
 */

#ifdef __APPLE__ 
# include <OpenCL/OpenCL.h> 
# else
# include <OpenCL/cl.h> 
#endif

#ifndef WOLF3D_H
# define WOLF3D_H
# define SCREEN_HEIGHT	600
# define SCREEN_WIDTH	800
# include "SDL2/SDL.h"
# include <unistd.h>

typedef struct			s_wolf3d
{
	SDL_Window			*win;
	SDL_Event			event;
	SDL_Renderer		*renderer;
	SDL_Surface			*surface;
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

typedef struct			s_cl
{
	int					err;
	cl_device_id		device_id;
	cl_context			context;
	cl_command_queue	commands;
	cl_program			program;
	cl_kernel			kernel;
	cl_mem				data;
	char				*wolf3d;
}						t_cl;

t_wolf3d				init_sdl();
void    				put_pixel_sdl(t_wolf3d wolf, int x, int y, t_color color);
void					destroy_sdl(t_wolf3d wolf);
t_cl					init_cl();

#endif