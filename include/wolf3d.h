/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetrell <npetrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 22:54:30 by mjoss             #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2020/11/25 21:56:46 by npetrell         ###   ########.fr       */
=======
/*   Updated: 2020/11/25 20:08:06 by mjoss            ###   ########.fr       */
>>>>>>> 667442b45bacdefd0a1fafba7120ab1c2e69da4c
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H
# define SCREEN_HEIGHT	500
# define SCREEN_WIDTH	500
# define VISIBILITY_RANGE 50
# define NUM_TEXTURES 1
# define SIZE_MAP 0.25
# include "SDL2/SDL.h"
# include "SDL2/SDL_image.h"
# include "SDL2/SDL_mixer.h"
# include "SDL2/SDL_ttf.h"
# include <unistd.h>
# include <math.h>
# include "map_parser.h"
# include "libft.h"

typedef struct			s_text
{
	TTF_Font			*font;
	SDL_Rect			rect;
	SDL_Surface			*text;
	SDL_Color			white;
	SDL_Color			black;
}						t_text;

typedef struct			s_color
{
	unsigned char		r;
	unsigned char		g;
	unsigned char		b;
}						t_color;

typedef struct			s_button
{
	SDL_Rect			rect;
	t_color				color;
	int					pressed;
	SDL_Window			*win;
	t_text				txt;
}						t_button;

typedef struct			s_logo
{
	SDL_Rect			rect;
	t_color				color;
}						t_logo;		

typedef struct			s_sounds
{
	Mix_Music			*bgm;
	Mix_Chunk			*sound_effect;
}						t_sounds;

typedef struct			s_texture
{
	SDL_Surface			*image;
	SDL_Texture			*texture;
}						t_texture;

typedef struct			s_wall
{
	int					num;
	t_texture			*north;
	t_texture			*south;
	t_texture			*east;
	t_texture			*west;
}						t_wall;

typedef struct			s_wolf3d
{
	SDL_Window			*win;
	SDL_Event			event;
	SDL_Renderer		*renderer;

	SDL_Surface			*sky_image;
	SDL_Texture			*sky_texture;

	Uint32				*pixels;
	int					is_running;
	int					is_hit;
	int					is_hit_down;

	float				factor;
	t_sounds			sound;
	t_map				*map;
	t_wall				*textures;
	t_button			button;
	t_logo				logo;
}						t_wolf3d;

typedef struct			s_ray
{
	float	ray_angle;
	float	hit_x;
	float	hit_y;
	float	ray_len;
}						t_ray;

typedef struct			s_player
{
	int		x;
	int		y;
	float	angle;
}						t_player;

typedef struct			s_pos
{
	int		x;
	int		y;
}						t_pos;

t_wolf3d				init_sdl();
//void    				put_pixel_sdl(t_wolf3d wolf, int x, int y, t_color color);
void					destroy_sdl(t_wolf3d wolf);

void					draw_map(t_map map, t_wolf3d *wolf);
void					draw_player(t_wolf3d *wolf, t_pos first, t_pos second);
void					draw_rays(t_map map, t_wolf3d *wolf, t_player player);
void					load_textures(t_wolf3d *wolf);
void					button_draw(t_wolf3d *wolf);
void					button_init(t_wolf3d *wolf);
void					logo_draw(t_wolf3d *wolf);
void 					free_wall(t_wall *wall_textures);
void					text_output(t_wolf3d *wolf);

#endif