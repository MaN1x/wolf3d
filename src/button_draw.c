#include "wolf3d.h"

void			button_draw(t_wolf3d *wolf)
{
	SDL_Surface	*button_surface;
	SDL_Texture	*button_texture;

	wolf->button.color.r = 100;
	wolf->button.color.g = 100;
	wolf->button.color.b = 100;
	wolf->button.rect.w = SCREEN_HEIGHT / 20;
	wolf->button.rect.h = SCREEN_HEIGHT / 20;
	wolf->button.rect.x = 0;
	wolf->button.rect.y = SCREEN_HEIGHT - wolf->button.rect.h;
	if ((button_surface = IMG_Load("textures/settings.png")) == NULL)
    	printf("imaged load fail\n");
    else
		printf("imaged load success\n");
	if ((button_texture = SDL_CreateTextureFromSurface(wolf->renderer, button_surface)) == NULL)
		printf("SDL create texture from surface fail: %s\n", SDL_GetError());
	else
		printf("SDL create texture from surface success\n");
	SDL_RenderCopy(wolf->renderer, button_texture, NULL, &wolf->button.rect);
	SDL_FreeSurface(button_surface);
	SDL_DestroyTexture(button_texture);
}