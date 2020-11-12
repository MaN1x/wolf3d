#include "wolf3d.h"

float			dist(x1, y1, x2, y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

void			draw_ray(t_map map, t_wolf3d *wolf, int x, int y, float player_angle)
{
    int         count_rays;
    int         ray;
    int         step_of_ray;
    int         count_steps;
    float       ray_x;
    float       ray_y;
    float       delta_ray_x;
    float       delta_ray_y;
    float       ray_angle;
    t_color     color;
    int         size_map;
    int			mapx;
    int			mapy;
    int			mapp;
    int			distT;


    count_rays = 60;
    count_steps = 8;
    ray = 0;
    ray_angle = player_angle - M_PI * 30 / 180;
	if (ray_angle < 0)
	{
		ray_angle += 2 * M_PI;
	}
	if (ray_angle > 2 * M_PI)
	{
		ray_angle -= 2 * M_PI;
	}
    color.r = 255;
    color.b = 245;
    color.g = 11;
    size_map = map.height * map.width;
    while (ray < count_rays)
    {
        step_of_ray = 0;
        float distH = 1000000;
        float hx = x;
        float hy = y;
		float htan = -1 / tan(ray_angle);
        if (ray_angle > M_PI && htan != 0)
        {
            ray_y = ((int)y / size_map) * size_map - 0.0001f;
            ray_x = (y - ray_y) * (htan) + x;
            delta_ray_y = -size_map;
            delta_ray_x = -delta_ray_y * (htan);
        }
        if (ray_angle < M_PI && htan != 0)
        {
            ray_y = ((int)y / size_map) * size_map + size_map;
            ray_x = (y - ray_y) * (htan) + x;
            delta_ray_y = size_map;
            delta_ray_x = -delta_ray_y * (htan);
        }
        if (ray_angle == 0 || ray_angle == M_PI)
        {
            delta_ray_x = x;
            delta_ray_y = y;
            step_of_ray = count_steps;
        }
        while (step_of_ray < count_steps)
        {
            mapx = (int)ray_x / size_map;
            mapy = (int)ray_y / size_map;
            if (mapx < map.height && mapy < map.width  && mapx >= 0 && mapy >= 0 && map.map[mapx][mapy] == 1)
            {
				hx = ray_x;
				hy = ray_y;
				distH = dist(x, y, hx, hy);
                step_of_ray = count_steps;
            }
            else
            {
                ray_x += delta_ray_x;
                ray_y += delta_ray_y;
                step_of_ray++;
            }
        }
        step_of_ray = 0;
        float distV = INFINITY;
        float vx = x;
        float vy = y;
        if (ray_angle > M_PI_2 && ray_angle < 3 *  M_PI_2)
        {
            ray_x = ((int)x / size_map) * size_map - 0.0001f;
            ray_y = (x - ray_x) * (-tan(ray_angle)) + y;
            delta_ray_x = -size_map;
            delta_ray_y = -delta_ray_x * (-tan(ray_angle));
        }
        if (ray_angle < M_PI_2 || ray_angle > 3 *  M_PI_2)
        {
            ray_x = ((int)x / size_map) * size_map + size_map;
            ray_y  = (x - ray_x) * (-tan(ray_angle)) + y;
            delta_ray_x = size_map;
            delta_ray_y = -delta_ray_x * (-tan(ray_angle));
        }
        if (ray_angle == 0 || ray_angle == M_PI)
        {
            delta_ray_x = x;
            delta_ray_y = y;
            step_of_ray = count_steps;
        }
        while (step_of_ray < count_steps)
        {
            mapx = (int)ray_x / size_map;
            mapy = (int)ray_y / size_map;
            if (mapx < map.height && mapy < map.width  && mapx >= 0 && mapy >= 0 && map.map[mapx][mapy] == 1)
            {
				vx = ray_x;
				vy = ray_y;
				distV = dist(x, y, vx, vy);
                step_of_ray = count_steps;
            }
            else
            {
                ray_x += delta_ray_x;
                ray_y += delta_ray_y;
                step_of_ray++;
            }
        }
		if (distV < distH)
		{
			ray_x = vx;
			ray_y = vy;
			distT = distV;
        	SDL_SetRenderDrawColor(wolf->renderer, 255, 0, 0, 255);
		}
		if (distH < distV)
		{
			ray_x = hx;
			ray_y = hy;
			distT = distH;
        	SDL_SetRenderDrawColor(wolf->renderer, 255, 245, 11, 255);
		}
        SDL_RenderDrawLine(wolf->renderer, (int)x, (int)y, (int)ray_x, (int)ray_y);

		//draw walls
		float ca = player_angle - ray_angle;
		if (ca < 0)
		{
			ca += 2 * M_PI;
		}
		if (ca > 2 * M_PI)
		{
			ca -= 2 * M_PI;
		}
		distT = distT * cos(ca);
		// 320 X 160 - window size for ray cast world
		float lineH;
		if (distT != 0)
			lineH = (size_map * 320) / distT;
		if (lineH > 320)
		{
			lineH = 320;
		}
		float lineO = 160 - lineH / 2;
		SDL_RenderDrawLine(wolf->renderer, (int)(ray * 8 + 530), (int)lineO, (int)(ray * 8 + 530), (int)(lineH + lineO));
		ray_angle += M_PI / 180;
		if (ray_angle < 0)
		{
			ray_angle += 2 * M_PI;
		}
		if (ray_angle > 2 * M_PI)
		{
			ray_angle -= 2 * M_PI;
		}
        ray++;
    }
}
