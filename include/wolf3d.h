/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoss <mjoss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 22:54:30 by mjoss             #+#    #+#             */
/*   Updated: 2020/11/17 22:54:30 by mjoss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H
# define SCREEN_HEIGHT	720
# define SCREEN_WIDTH	1024
# define VISIBILITY_RANGE 8
# include "SDL2/SDL.h"
# include "SDL2/SDL_image.h"
# include "SDL2/SDL_mixer.h"
# include <unistd.h>
# include <math.h>
# include "map_parser.h"

typedef struct			s_sounds
{
	Mix_Music			*bgm;
	Mix_Chunk			*sound_effect;
}						t_sounds;

typedef struct			s_wolf3d
{
	SDL_Window			*win;
	SDL_Event			event;
	SDL_Renderer		*renderer;

	SDL_Surface			*image;
	SDL_Texture			*texture;

	SDL_Surface			*sky_image;
	SDL_Texture			*sky_texture;

	Uint32				*pixels;
	int					is_running;
	int					is_hit;
	t_sounds			sound;
}						t_wolf3d;

typedef struct			s_color
{
	unsigned char		r;
	unsigned char		g;
	unsigned char		b;
}						t_color;

typedef struct			s_ray
{
	float	ray_angle;
	float	hit_x;
	float	hit_y;
	int		ray_len;
}						t_ray;

t_wolf3d				init_sdl();
void    				put_pixel_sdl(t_wolf3d wolf, int x, int y, t_color color);
void					destroy_sdl(t_wolf3d wolf);

void					draw_map(t_map map, t_wolf3d *wolf);
void            		draw_player(t_wolf3d *wolf, int x, int y, int dx, int dy);
void					draw_rays(t_map map, t_wolf3d *wolf, float x, float y, float player_alpha);

#endif