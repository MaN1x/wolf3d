#include "wolf3d.h"

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
	SDL_SetRenderDrawColor(wolf->renderer, color.r, color.g, color.b, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawLine(wolf->renderer, x, y, x + dx * 5, y + dy * 5);
}
