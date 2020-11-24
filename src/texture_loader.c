/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_loader.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoss <mjoss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 19:59:53 by mjoss             #+#    #+#             */
/*   Updated: 2020/11/24 17:28:23 by mjoss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <stdlib.h>
#include <stdio.h>

static t_texture	*create_texture(t_wolf3d *wolf, const char *path)
{
	t_texture	*texture;

	if ((texture = (t_texture*)malloc(sizeof(t_texture))) == NULL)
	{
		printf("malloc error\n");
		exit(EXIT_FAILURE);
	}
	if ((texture->image = IMG_Load(path)) == NULL)
	{
		printf("texture load failure\n");
		exit(EXIT_FAILURE);
	}
	if ((texture->texture = SDL_CreateTextureFromSurface(wolf->renderer, texture->image)) == NULL)
	{
		printf("SDL create texture from surface failure\n");
		exit(EXIT_FAILURE);
	}
	return (texture);
}

void free_textures(t_texture *texture)
{
	SDL_FreeSurface(texture->image);
	texture->image = NULL;
	SDL_DestroyTexture(texture->texture);
	texture->texture = NULL;
}

void free_wall(t_wall *wall_textures)
{
	int i;

	i = 1;
	while (i < NUM_TEXTURES + 1)
	{
		free_textures(wall_textures[i].north);
		free(wall_textures[i].north);
		wall_textures[i].north = NULL;

		free_textures(wall_textures[i].south);
		free(wall_textures[i].south);
		wall_textures[i].south = NULL;

		free_textures(wall_textures[i].east);
		free(wall_textures[i].east);
		wall_textures[i].east = NULL;

		free_textures(wall_textures[i].west);
		free(wall_textures[i].west);
		wall_textures[i].west = NULL;
		i++;
	}
	free(wall_textures);
}

void	load_textures(t_wolf3d *wolf)
{
	t_wall			*wall_textures;


	if ((wall_textures = (t_wall*)malloc(sizeof(t_wall) * (NUM_TEXTURES + 1))) == NULL)
	{
		printf("malloc error\n");
		exit(EXIT_FAILURE);
	}
	wall_textures[0].num = 0;
	wall_textures[0].north = NULL;
	wall_textures[0].south = NULL;
	wall_textures[0].east = NULL;
	wall_textures[0].west = NULL;


	wall_textures[1].num = 1;
	wall_textures[1].north = create_texture(wolf, "textures/1.N.jpg");
	wall_textures[1].south = create_texture(wolf, "textures/1.S.jpg");
	wall_textures[1].east = create_texture(wolf, "textures/1.E.jpg");
	wall_textures[1].west = create_texture(wolf, "textures/1.W.jpg");

//	wall_textures[2].num = 2;
//	wall_textures[2].north = create_texture(wolf, "textures/");
//	wall_textures[2].south = create_texture(wolf, "textures/");
//	wall_textures[2].east = create_texture(wolf, "textures/");
//	wall_textures[2].west = create_texture(wolf, "textures/");
	wolf->textures = wall_textures;
}
