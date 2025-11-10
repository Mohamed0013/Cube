/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw2Dmaputils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohdahma <mohdahma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 12:51:01 by mohdahma          #+#    #+#             */
/*   Updated: 2025/11/08 12:51:02 by mohdahma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void	draw_floor(t_game *game, int x, int *y, unsigned int floor)
{
	while (*y < HEIGHT / 2)
	{
		x = 0;
		while (x < WIDTH)
		{
			set_pixel_image(&game->current_scene, x, *y, floor);
			x++;
		}
		(*y)++;
	}
}

void	draw_ceil(t_game *game, int x, int y, unsigned int ceil)
{
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			set_pixel_image(&game->current_scene, x, y, ceil);
			x++;
		}
		y++;
	}
}
