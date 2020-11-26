/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoss <mjoss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 04:07:18 by mjoss             #+#    #+#             */
/*   Updated: 2020/11/26 18:48:29 by mjoss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include "libft.h"

void	check_map(int argc, char *path, t_map *map)
{
	int			map_status;

	if (argc != 2)
	{
		ft_putstr("wrong number of arguments\n");
		exit(0);
	}
	if ((map_status = parse_map(path, map)) == -1)
	{
		ft_putstr("wrong map\n");
		exit(0);
	}
	else if (map_status == 0)
		exit(0);
}

void	main_loop(t_wolf3d *wolf, t_player *player, float *dx, float *dy)
{
	while (wolf->is_running)
		while (SDL_PollEvent(&wolf->event))
		{
			if (wolf->event.type == SDL_QUIT || (wolf->event.type == SDL_KEYDOWN
			&& wolf->event.key.keysym.sym == SDLK_ESCAPE))
				wolf->is_running = 0;
			if (wolf->event.type == SDL_WINDOWEVENT &&
				wolf->event.window.event == SDL_WINDOWEVENT_CLOSE)
			{
				wolf->button.pressed = 0;
				SDL_HideWindow(wolf->button.win);
				SDL_DestroyWindow(wolf->button.win);
			}
			if (wolf->event.type == SDL_KEYDOWN)
			{
				music_control(*wolf);
				movement(*wolf, player, dx, dy);
			}
			wolf->is_hit = 0;
			wolf->is_hit_down = 0;
			draw_all(wolf, *player, *dx, *dy);
			button_init(wolf);
			SDL_RenderPresent(wolf->renderer);
		}
}

int		main(int argc, char **argv)
{
	t_wolf3d	wolf;
	t_player	player;
	float		player_dx;
	float		player_dy;
	t_map		map;

	check_map(argc, argv[1], &map);
	wolf = init_sdl();
	wolf.factor = (SCREEN_WIDTH / 16);
	player.x = map.player_position.x * wolf.factor;
	player.y = map.player_position.y * wolf.factor;
	player.angle = 0;
	player_dx = cos(player.angle) * 5;
	player_dy = sin(player.angle) * 5;
	wolf.map = &map;
	wolf.is_running = 1;
	main_loop(&wolf, &player, &player_dx, &player_dy);
	free_wall(wolf.textures);
	destroy_sdl(wolf);
	return (0);
}
