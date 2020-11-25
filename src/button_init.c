/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetrell <npetrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 20:40:04 by npetrell          #+#    #+#             */
/*   Updated: 2020/11/25 20:47:15 by npetrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		button_locate(t_wolf3d *wolf)
{
	return (wolf->event.button.x >= wolf->button.rect.x &&
	wolf->event.button.x <= (wolf->button.rect.x + wolf->button.rect.w) &&
	wolf->event.button.y >= wolf->button.rect.y &&
	wolf->event.button.y <= (wolf->button.rect.y + wolf->button.rect.h));
}

void	gui(t_wolf3d *wolf)
{
	if ((wolf->button.win = SDL_CreateWindow("Settings",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 500, 160, 0)) == NULL)
	{
		ft_putstr("Window create fail\n");
		exit(-1);
	}
	text_output(wolf);
}

void	button_init(t_wolf3d *wolf)
{
	if (wolf->event.type == SDL_MOUSEBUTTONDOWN)
	{
		if (wolf->event.button.button == SDL_BUTTON_LEFT
					&& button_locate(wolf)
					&& wolf->button.pressed == 0)
		{
			wolf->button.pressed = 1;
			gui(wolf);
		}
	}
}
