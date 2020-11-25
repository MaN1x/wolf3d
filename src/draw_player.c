#include "wolf3d.h"

void            draw_player(t_wolf3d *wolf, int x, int y, int dx, int dy)
{
    t_color     color;
    SDL_Rect    r;

	r.w = (SCREEN_WIDTH * SIZE_MAP) / wolf->map->width;
	r.h = (SCREEN_HEIGHT * SIZE_MAP) / wolf->map->height;
	r.x = x / wolf->factor * r.w;
	r.y = y / wolf->factor * r.h;
    r.w = 3;
	r.h = 3;
    color.r = 255;
    color.b = 255;
    color.g = 255;
    SDL_SetRenderDrawColor( wolf->renderer, color.r, color.g, color.b, 255);
    SDL_RenderFillRect(wolf->renderer, &r);
	SDL_SetRenderDrawColor(wolf->renderer, color.r, color.g, color.b, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawLine(wolf->renderer, r.x, r.y, r.x + dx * 5, r.y + dy * 5);
}
