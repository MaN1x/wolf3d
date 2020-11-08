/*
 * Filename: /Users/Student/mandelbrot/put_pixel_sdl.c
 * Path: /Users/Student/mandelbrot
 * Created Date: Tuesday, May 12th 2020, 11:13:05 pm
 * Author: Student
 * 
 * Copyright (c) 2020 Your Company
 */

#include "wolf3d.h"

void    put_pixel_sdl(t_wolf3d wolf, int x, int y, t_color color)
{
    if (x > 0 && x <= SCREEN_WIDTH && y > 0 && y <= SCREEN_HEIGHT)
    {
        ((unsigned char*)wolf.pixels)[4 * (y * SCREEN_WIDTH + x) + 0] = color.b;
        ((unsigned char*)wolf.pixels)[4 * (y * SCREEN_WIDTH + x) + 1] = color.g;
        ((unsigned char*)wolf.pixels)[4 * (y * SCREEN_WIDTH + x) + 2] = color.r;
        ((unsigned char*)wolf.pixels)[4 * (y * SCREEN_WIDTH + x) + 3] = 1;
    }
}