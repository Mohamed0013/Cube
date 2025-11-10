/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw2Dmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohdahma <mohdahma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 12:50:53 by mohdahma          #+#    #+#             */
/*   Updated: 2025/11/08 12:50:54 by mohdahma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

t_rgb	clr_to_rgb(unsigned int color)
{
	t_rgb	rgb;

	rgb.r = (color >> 16) & 0xFF;
	rgb.g = (color >> 8) & 0xFF;
	rgb.b = color & 0xFF;
	return (rgb);
}

t_rgb	apply_shading(t_rgb rgb, double wall_dist)
{
	double	shading;

	shading = 1.0 - (wall_dist / MAX_DISTANCE);
	if (shading < 0.0)
		shading = 0.0;
	rgb.r = (int)(rgb.r * shading);
	rgb.g = (int)(rgb.g * shading);
	rgb.b = (int)(rgb.b * shading);
	return (rgb);
}

t_rgb	itorgb(int *color)
{
	t_rgb	rgb;

	rgb.r = color[0];
	rgb.g = color[1];
	rgb.b = color[2];
	return (rgb);
}

unsigned int	rgb_to_uint(t_rgb rgb)
{
	return ((rgb.r << 16) | (rgb.g << 8) | rgb.b);
}

void	draw_floor_ceil(t_game *game)
{
	t_rgb			rgb_floor;
	t_rgb			rgb_ceil;
	unsigned int	floor;
	unsigned int	ceil;

	int (y) = 0;
	rgb_floor = itorgb(game->parsing->mapcolor[0]);
	rgb_ceil = itorgb(game->parsing->mapcolor[1]);
	floor = rgb_to_uint(rgb_floor);
	ceil = rgb_to_uint(rgb_ceil);
	draw_floor(game, 0, &y, floor);
	draw_ceil(game, 0, y, ceil);
}
