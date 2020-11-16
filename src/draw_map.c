#include "wolf3d.h"

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
