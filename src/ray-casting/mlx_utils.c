/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohdahma <mohdahma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 15:08:34 by mohdahma          #+#    #+#             */
/*   Updated: 2025/11/11 15:09:49 by mohdahma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shared.h"

int	render_game(t_game *game)
{
	setup_scene(game);
	raycaster(game);
	mlx_put_image_to_window(game->mlx->mlx, game->mlx->win,
		game->current_scene.img, 0, 0);
	mlx_destroy_image(game->mlx->mlx, game->current_scene.img);
	return (0);
}

void	second_part(t_game *game, double delta)
{
	int	moved;
	int	rotated;

	game->frame = delta;
	game->player->move_speed = game->frame * SPEED;
	game->player->rot_speed = game->frame * ROT_SPEED;
	moved = move_player(game);
	rotated = game->player->is_moving;
	if (moved || rotated)
		render_game(game);
	game->player->is_moving = 0;
}

int	render(t_game *game)
{
	static struct timespec	last;
	double					delta;
	struct timespec			now;

	if (clock_gettime(CLOCK_MONOTONIC, &now) == -1)
		delta = 1.0 / 60.0;
	else if (last.tv_sec == 0 && last.tv_nsec == 0)
	{
		last = now;
		delta = 1.0 / 60.0;
	}
	else
	{
		delta = (now.tv_sec - last.tv_sec) + (now.tv_nsec - last.tv_nsec) / 1e9;
		if (delta <= 0 || delta > 1.0)
			delta = 1.0 / 60.0;
		last = now;
	}
	second_part(game, delta);
	return (0);
}
