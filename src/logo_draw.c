#include "wolf3d.h"

void			logo_draw(t_wolf3d *wolf)
{
	SDL_Surface	*logo_surface;
	SDL_Texture	*logo_texture;

	wolf->logo.color.r = 100;
	wolf->logo.color.g = 100;
	wolf->logo.color.b = 100;
	wolf->logo.rect.w = SCREEN_WIDTH / 10;
	wolf->logo.rect.h = SCREEN_HEIGHT / 20;
	wolf->logo.rect.x = SCREEN_WIDTH - wolf->logo.rect.w;
	wolf->logo.rect.y = SCREEN_HEIGHT - wolf->logo.rect.h;
	if ((logo_surface = IMG_Load("textures/logo.png")) == NULL)
    	printf("imaged load fail\n");
    else
		printf("imaged load success\n");
	if ((logo_texture = SDL_CreateTextureFromSurface(wolf->renderer, logo_surface)) == NULL)
		printf("SDL create texture from surface fail: %s\n", SDL_GetError());
	else
		printf("SDL create texture from surface success\n");
	SDL_RenderCopy(wolf->renderer, logo_texture, NULL, &wolf->logo.rect);
	SDL_FreeSurface(logo_surface);
	SDL_DestroyTexture(logo_texture);
}