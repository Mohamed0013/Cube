/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohdahma <mohdahma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 12:51:33 by mohdahma          #+#    #+#             */
/*   Updated: 2025/11/11 17:33:35 by mohdahma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shared.h"

void	calcultate_wall_dist(t_ray *ray, t_game *cam)
{
	if (ray->side == 0)
		ray->wall_dist = (ray->side_dist.x - ray->delta_dist.x);
	else
		ray->wall_dist = (ray->side_dist.y - ray->delta_dist.y);
	ray->wall_dist *= cos(cam->player->angle - vec2_to_angle(ray->dir));
}

void	get_wall_dist(t_game *game, t_ray *ray, double t[3])
{
	int (hit) = 0;
	while (hit == 0)
	{
		if (ray->side_dist.x < ray->side_dist.y)
		{
			ray->side_dist.x += ray->delta_dist.x;
			t[0] += ray->step.x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist.y += ray->delta_dist.y;
			t[1] += ray->step.y;
			ray->side = 1;
		}
		if (game->parsing->map[(int)t[1]][(int)t[0]] == '1')
		{
			calcultate_wall_dist(ray, game);
			hit = 1;
		}
	}
}

void	set_delta(t_ray *ray)
{
	if (ray->dir.x == 0)
		ray->delta_dist.x = INFINITY;
	else
		ray->delta_dist.x = fabs(1.0 / ray->dir.x);
	if (ray->dir.y == 0)
		ray->delta_dist.y = INFINITY;
	else
		ray->delta_dist.y = fabs(1.0 / ray->dir.y);
}

void	raycaster(t_game *game)
{
	t_ray		ray;
	t_player	*plyr;

	size_t (number_of_rays) = WIDTH, (i) = 0;
	double (camera_x), (map_x), (map_y);
	plyr = game->player;
	while (i < number_of_rays)
	{
		map_x = (int)(game->player->pos.x);
		map_y = (int)(game->player->pos.y);
		camera_x = 2.0 * ((double)i / (double)(number_of_rays - 1))
			- 1.0;
		ray.dir = add_vec2(plyr->dir, vec2_scale(plyr->plane, camera_x));
		vec2_normalized(&ray.dir);
		set_delta(&ray);
		ray.side_dist = determine_first_side(plyr->pos, map_x, map_y, &ray);
		get_wall_dist(game, &ray, (double [3]){map_x, map_y, camera_x});
		calculate_line_wall_x(game, &ray);
		update_texture(game, &ray, i);
		i++;
	}
}
