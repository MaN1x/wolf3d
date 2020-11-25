#include "wolf3d.h"

void			text_output(t_wolf3d *wolf)
{
	SDL_Renderer *renderer;
	TTF_Init();
    if (!(wolf->button.txt.font = TTF_OpenFont("lib/game.ttf", 40)))
	{
		ft_putstr("problem loading font");
		exit(0);
	}
	if (!(renderer = SDL_CreateRenderer(wolf->button.win, -1, 0)))
		printf("SDL create Renderer fail: %s\n", SDL_GetError());
	else
		printf("SDL create Renderer success\n");
    SDL_Color color = {200, 12, 12};


	SDL_Surface * surface = TTF_RenderText_Solid(wolf->button.txt.font,
		"Change direction moving key_buttons              LEFT/RIGHT   |    A/D", color);
	SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, surface);
	wolf->button.txt.rect.h = 32;
	wolf->button.txt.rect.w = 450;
	wolf->button.txt.rect.x = 25;
	wolf->button.txt.rect.y = 0;
	SDL_RenderCopy(renderer, texture, NULL, &wolf->button.txt.rect);
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);


	surface = TTF_RenderText_Solid(wolf->button.txt.font,
		"Change movement key_buttons         UP/DOWN    |    W/S", color);
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	wolf->button.txt.rect.h = 32;
	wolf->button.txt.rect.w = 450;
	wolf->button.txt.rect.x = 25;
	wolf->button.txt.rect.y = 42;
	SDL_RenderCopy(renderer, texture, NULL, &wolf->button.txt.rect);
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);

	surface = TTF_RenderText_Solid(wolf->button.txt.font,
		"Play/Stop/Pause music        P/S/Q", color);
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	wolf->button.txt.rect.h = 32;
	wolf->button.txt.rect.w = 450;
	wolf->button.txt.rect.x = 25;
	wolf->button.txt.rect.y = 84;
	SDL_RenderCopy(renderer, texture, NULL, &wolf->button.txt.rect);
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);

	surface = TTF_RenderText_Solid(wolf->button.txt.font,
		"Exit from program       Esc", color);
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	wolf->button.txt.rect.h = 32;
	wolf->button.txt.rect.w = 450;
	wolf->button.txt.rect.x = 25;
	wolf->button.txt.rect.y = 126;
	SDL_RenderCopy(renderer, texture, NULL, &wolf->button.txt.rect);
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);

	SDL_RenderPresent(renderer);
	TTF_CloseFont(wolf->button.txt.font);
}

void            gui(t_wolf3d *wolf)
{
	if ((wolf->button.win = SDL_CreateWindow("Settings",
				SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 500, 160, 0)) == NULL)
		printf("Window create fail\n");
	else
		printf("Window create success\n");
	text_output(wolf);
}

void			button_init(t_wolf3d *wolf)
{
	if (wolf->event.type == SDL_MOUSEBUTTONDOWN) {
        if (wolf->event.button.button == SDL_BUTTON_LEFT &&
                wolf->event.button.x >= wolf->button.rect.x &&
                wolf->event.button.x <= (wolf->button.rect.x + wolf->button.rect.w) &&
                wolf->event.button.y >= wolf->button.rect.y &&
                wolf->event.button.y <= (wolf->button.rect.y + wolf->button.rect.h) && wolf->button.pressed == 0)
        {
			wolf->button.pressed = 1;
            gui(wolf);
        }
    }
}