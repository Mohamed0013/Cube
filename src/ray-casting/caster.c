/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   caster.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohdahma <mohdahma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 12:50:48 by mohdahma          #+#    #+#             */
/*   Updated: 2025/11/11 13:48:36 by mohdahma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shared.h"

t_vec2	determine_first_side(t_vec2 pos, int map_x, int map_y, t_ray *ray)
{
	t_vec2			first_side;
	const double	tile_posx = pos.x;
	const double	tile_posy = pos.y;

	if (ray->dir.x < 0)
	{
		first_side.x = (tile_posx - map_x) * ray->delta_dist.x;
		ray->step.x = -1;
	}
	else
	{
		first_side.x = (map_x + 1.0 - tile_posx) * ray->delta_dist.x;
		ray->step.x = 1;
	}
	if (ray->dir.y < 0)
	{
		first_side.y = (tile_posy - map_y) * ray->delta_dist.y;
		ray->step.y = -1;
	}
	else
	{
		first_side.y = (map_y + 1.0 - tile_posy) * ray->delta_dist.y;
		ray->step.y = 1;
	}
	return (first_side);
}

void	calculate_line_wall_x(t_game *game, t_ray *ray)
{
	const double	real_dist = ray->wall_dist
		/ cos(game->player->angle - vec2_to_angle(ray->dir));

	ray->line_height = (int)(HEIGHT / ray->wall_dist);
	ray->draw_start = (HEIGHT / 2) - (ray->line_height / 2);
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->draw_start + ray->line_height;
	if (ray->draw_end >= HEIGHT)
		ray->draw_end = HEIGHT - 1;
	if (ray->side == 0)
		ray->wall_x = game->player->pos.y + real_dist * ray->dir.y;
	else
		ray->wall_x = game->player->pos.x + real_dist * ray->dir.x;
	ray->wall_x -= floor(ray->wall_x);
}

void	set_frame_pixel(t_img *img, t_game *game, int x, int y)
{
	t_rgb			rgb_floor;
	t_rgb			rgb_ceil;
	unsigned int	floor;
	unsigned int	ceil;
	t_texture		*texture;

	rgb_floor = itorgb(game->parsing->mapcolor[0]);
	rgb_ceil = itorgb(game->parsing->mapcolor[1]);
	floor = rgb_to_uint(rgb_floor);
	ceil = rgb_to_uint(rgb_ceil);
	texture = game->texture;
	if (texture->screen_pixels[y][x] > 0)
		set_pixel_image(img, x, y, texture->screen_pixels[y][x]);
	else if (y < HEIGHT / 2)
		set_pixel_image(img, x, y, floor);
	else if (y < HEIGHT - 1)
		set_pixel_image(img, x, y, ceil);
}

void	render_frame(t_game *game)
{
	t_img	img;
	int		x;
	int		y;

	init_img_clean(&img);
	img.img = mlx_new_image(game->mlx->mlx, WIDTH, HEIGHT);
	img.addr = (int *)mlx_get_data_addr(img.img, &img.bits_per_pixel,
			&img.line_length, &img.endian);
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			set_frame_pixel(&img, game, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(game->mlx->mlx, game->mlx->win, img.img, 0, 0);
	mlx_destroy_image(game->mlx->mlx, img.img);
}
