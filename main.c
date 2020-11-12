/*
 * Filename: /Users/Student/mandelbrot/main.c
 * Path: /Users/Student/mandelbrot
 * Created Date: Tuesday, May 12th 2020, 9:35:08 pm
 * Author: Student
 * 
 * Copyright (c) 2020 Your Company
 */

#include "wolf3d.h"
#include "map_parser.h"
#include "libft.h"
#include <stdio.h>

float			dist(x, y, hx, hy, alpha)
{
	return (sqrt((hx - x) * (hx - x) + (hy - y) * (hy - y)));
}

void			draw_ray(t_map map, t_wolf3d *wolf, int x, int y, float player_alpha)
{
    int         count_rays;
    int         ray;
    int         step_of_ray;
    int         count_steps;
    float       ray_x;
    float       ray_y;
    float       delta_ray_x;
    float       delta_ray_y;
    float       ray_alpha;
    t_color     color;
    int         size_map;
    int			mapx;
    int			mapy;
    int			mapp;
    int			distT;


    count_rays = 60;
    count_steps = 8;
    ray = 0;
    ray_alpha = player_alpha - M_PI * 30 / 180;
	if (ray_alpha < 0)
	{
		ray_alpha += 2 * M_PI;
	}
	if (ray_alpha > 2 * M_PI)
	{
		ray_alpha -= 2 * M_PI;
	}
    color.r = 255;
    color.b = 245;
    color.g = 11;
    size_map = map.height * map.width;
    while (ray < count_rays)
    {
        step_of_ray = 0;
        float distH = 1000000;
        float hx = x;
        float hy = y;
        if (ray_alpha > M_PI)
        {
            ray_y = ((int)y / size_map) * size_map - 0.0001;
            ray_x = (y - ray_y) * (-1 / tan(ray_alpha)) + x;
            delta_ray_y = -size_map;
            delta_ray_x = -delta_ray_y * (-1 / tan(ray_alpha));
        }
        if (ray_alpha < M_PI)
        {
            ray_y = ((int)y / size_map) * size_map + size_map;
            ray_x = (y - ray_y) * (-1 / tan(ray_alpha)) + x;
            delta_ray_y = size_map;
            delta_ray_x = -delta_ray_y * (-1 / tan(ray_alpha));
        }
        if (ray_alpha == 0 || ray_alpha == M_PI)
        {
            delta_ray_x = x;
            delta_ray_y = y;
            step_of_ray = count_steps;
        }
        while (step_of_ray < count_steps)
        {
            mapx = (int)ray_x / size_map;
            mapy = (int)ray_y / size_map;
            if (mapx < map.height && mapy < map.width  && mapx >= 0 && mapy >= 0 && map.map[mapx][mapy] == 1)
            {
				hx = ray_x;
				hy = ray_y;
				distH = dist(x, y, hx, hy, ray_alpha);
                step_of_ray = count_steps;
            }
            else
            {
                ray_x += delta_ray_x;
                ray_y += delta_ray_y;
                step_of_ray++;
            }
        }
        step_of_ray = 0;
        float distV = 1000000;
        float vx = x;
        float vy = y;
        if (ray_alpha > M_PI_2 && ray_alpha < 3 *  M_PI_2)
        {
            ray_x = ((int)x / size_map) * size_map - 0.0001;
            ray_y = (x - ray_x) * (-tan(ray_alpha)) + y;
            delta_ray_x = -size_map;
            delta_ray_y = -delta_ray_x * (-tan(ray_alpha));
        }
        if (ray_alpha < M_PI_2 || ray_alpha > 3 *  M_PI_2)
        {
            ray_x = ((int)x / size_map) * size_map + size_map;
            ray_y  = (x - ray_x) * (-tan(ray_alpha)) + y;
            delta_ray_x = size_map;
            delta_ray_y = -delta_ray_x * (-tan(ray_alpha));
        }
        if (ray_alpha == 0 || ray_alpha == M_PI)
        {
            delta_ray_x = x;
            delta_ray_y = y;
            step_of_ray = count_steps;
        }
        while (step_of_ray < count_steps)
        {
            mapx = (int)ray_x / size_map;
            mapy = (int)ray_y / size_map;
            if (mapx < map.height && mapy < map.width  && mapx >= 0 && mapy >= 0 && map.map[mapx][mapy] == 1)
            {
				vx = ray_x;
				vy = ray_y;
				distV = dist(x, y, vx, vy, ray_alpha);
                step_of_ray = count_steps;
            }
            else
            {
                ray_x += delta_ray_x;
                ray_y += delta_ray_y;
                step_of_ray++;
            }
        }
		if (distV < distH)
		{
			ray_x = vx;
			ray_y = vy;
			distT = distV;
        	SDL_SetRenderDrawColor(wolf->renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
		}
		if (distH < distV)
		{
			ray_x = hx;
			ray_y = hy;
			distT = distH;
        	SDL_SetRenderDrawColor(wolf->renderer, 255, 245, 11, SDL_ALPHA_OPAQUE);
		}
        SDL_RenderDrawLine(wolf->renderer, x, y, ray_x, ray_y);

		float ca = player_alpha - ray_alpha;
		if (ca < 0)
		{
			ca += 2 * M_PI;
		}
		if (ca > 2 * M_PI)
		{
			ca -= 2 * M_PI;
		}
		distT = distT * cos(ca);
		float lineH = (size_map * 320) / distT;
		if (lineH > 320)
		{
			lineH = 320;
		}
		float lineO = 160 - lineH / 2;
		SDL_RenderDrawLine(wolf->renderer, ray * 8 + 530, lineO, ray * 8 + 530, lineH + lineO);
        ray++;
		ray_alpha += M_PI / 180;
		if (ray_alpha < 0)
		{
			ray_alpha += 2 * M_PI;
		}
		if (ray_alpha > 2 * M_PI)
		{
			ray_alpha -= 2 * M_PI;
		}
    }
}

void            draw_map(t_map map, t_wolf3d *wolf)
{
   int x, y, xo, yo;

	x = 0;
	y = 0;
	SDL_Rect r;
	t_color color;

    int map_size = map.width * map.height;
    while (y < map.width)
    {
		x = 0;
        while (x < map.height)
        {
			if (map.map[x][y] == 1)
			{
				color.r = 84;
				color.g = 57;
				color.b = 0;
			}
			else
			{
				color.r = 117;
				color.g = 77;
				color.b = 0;	
			}
			r.w = map_size;
    		r.h = map_size;
			r.x = x * map_size;
			r.y = y * map_size;

			SDL_SetRenderDrawColor( wolf->renderer, color.r, color.g, color.b, SDL_ALPHA_OPAQUE);
			SDL_RenderFillRect(wolf->renderer, &r);
            x++;
        }
        y++;
    }
}

void            draw_player(t_wolf3d *wolf, int x, int y, int dx, int dy)
{
    t_color     color;
    SDL_Rect    r;

    r.x = x;
    r.y = y;
    r.w = 5;
    r.h = 5;
    color.r = 255;
    color.b = 255;
    color.g = 255;
    SDL_SetRenderDrawColor( wolf->renderer, color.r, color.g, color.b, 255);
    SDL_RenderFillRect(wolf->renderer, &r);
	//wolf->pixels[x + y * SCREEN_WIDTH] = 0xffffff;
	//SDL_RenderClear(wolf->renderer);
	//SDL_UpdateTexture(wolf->texture, NULL, wolf->pixels, SCREEN_WIDTH * sizeof(Uint32));

	SDL_SetRenderDrawColor(wolf->renderer, color.r, color.g, color.b, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawLine(wolf->renderer, x, y, x + dx * 5, y + dy * 5);
}

void			fill_background(t_wolf3d *wolf)
{
	SDL_SetRenderDrawColor( wolf->renderer, 128, 128, 128, 255);
	SDL_RenderClear(wolf->renderer);
}


int             main(int argc, char **argv)
{
    t_wolf3d	wolf;
    int			mapX = 8;
    int			mapY = 8;
    int			mapS = 64;
	float		player_x = 100;
    float		player_y = 100;
	float		player_dx;
	float		player_dy;
	float		player_alpha = 0;
	int			map_status;
	t_map		map;

	if ((map_status = parse_map(argv[1], &map)) == -1)
    {
		ft_putstr("wrong map\n");
        exit (0);
    }
	else if (map_status == 0)
	{
		ft_putstr("syscall err\n");
		exit (0);
	}
	player_dx = cos(player_alpha) * 5;
	player_dy = sin(player_alpha) * 5;
    wolf = init_sdl();
    wolf.is_running = 1;
    while (wolf.is_running) {
        while (SDL_PollEvent(&wolf.event)) {
            if (wolf.event.type == SDL_QUIT || wolf.event.key.keysym.sym == SDLK_ESCAPE) {
                wolf.is_running = 0;
            }
            if (wolf.event.type == SDL_KEYDOWN)
            {
                if (wolf.event.key.keysym.sym == SDLK_DOWN)
				{
					player_alpha -= 0.1;
					if (player_alpha < 0)
						player_alpha += 2 * M_PI;
					player_dx = cos(player_alpha) * 5;
					player_dy = sin(player_alpha) * 5;
				}
                else if (wolf.event.key.keysym.sym == SDLK_UP)
				{
					player_alpha += 0.1;
					if (player_alpha > 2 * M_PI)
						player_alpha -= 2 * M_PI;
					player_dx = cos(player_alpha) * 5;
					player_dy = sin(player_alpha) * 5;
				}
                else if (wolf.event.key.keysym.sym == SDLK_RIGHT)
				{
                    player_x += player_dx;
					player_y += player_dy;
				}
                else if (wolf.event.key.keysym.sym == SDLK_LEFT)
				{
					player_x -= player_dx;
                    player_y -= player_dy;
				}
            }
    	}
		fill_background(&wolf);
		draw_map(map, &wolf);
    	//SDL_RenderCopy(wolf.renderer, wolf.texture, NULL, NULL);
        draw_ray(map, &wolf, player_x, player_y, player_alpha);
        draw_player(&wolf, player_x, player_y, player_dx, player_dy);
		//SDL_RenderClear(wolf.renderer);
		//SDL_UpdateTexture(wolf.texture, NULL, wolf.pixels, SCREEN_WIDTH * sizeof(Uint32));
        SDL_RenderPresent(wolf.renderer);
	}
    destroy_sdl(wolf);
    return (0);
}

/*
	wolf.pixels[x + y * SCREEN_WIDTH] = 0xfff000;
	SDL_RenderClear(wolf.renderer);
	SDL_UpdateTexture(wolf.texture, NULL, wolf.pixels, SCREEN_WIDTH * sizeof(Uint32));
    SDL_RenderCopy(wolf.renderer, wolf.texture, NULL, NULL);
*/