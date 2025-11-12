/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohdahma <mohdahma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 12:45:10 by mohdahma          #+#    #+#             */
/*   Updated: 2025/11/12 12:47:58 by mohdahma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

#define COLLISION_RADIUS 0.1

static int	key_release(int key, t_game *game)
{
	t_player	*player;

	player = game->player;
	if (key == W_KEY && player->move_forward)
		player->move_forward = 0;
	if (key == S_KEY && player->move_back)
		player->move_back = 0;
	if (key == A_KEY && player->move_left)
		player->move_left = 0;
	if (key == D_KEY && player->move_right)
		player->move_right = 0;
	if (key == LEFT_KEY && player->rotate == 1)
		player->rotate = 0;
	if (key == RIGHT_KEY && player->rotate == -1)
		player->rotate = 0;
	game->player = player;
	return (0);
}

int	key_press(int key, t_game *game)
{
	t_player	*player;

	player = game->player;
	if (key == ESC_KEY)
		close_window(game);
	if (key == W_KEY)
		player->move_forward = 1;
	if (key == S_KEY)
		player->move_back = 1;
	if (key == A_KEY)
		player->move_left = 1;
	if (key == D_KEY)
		player->move_right = 1;
	if (key == LEFT_KEY)
		player->rotate = 1;
	if (key == RIGHT_KEY)
		player->rotate = -1;
	if (key == 'm' || key == 'M')
	{
		toggle_mouse(game);
		player->is_moving = 1;
	}
	game->player = player;
	return (0);
}

int	move_player(t_game *game)
{
	t_player	*player;
	t_vec2		new_pos;
	int			map_y;

	int (moved), (map_x);
	player = game->player;
	new_pos = game->player->pos;
	moved = 0;
	handle_movement(player, &new_pos, &moved);
	handle_rotation(player, &moved);
	map_x = (int)(new_pos.x);
	map_y = (int)(new_pos.y);
	if (game->parsing->map[map_y][(int)((new_pos.x - COLLISION_RADIUS))] != '1'
		&& game->parsing->map[map_y][(int)((new_pos.x
				+ COLLISION_RADIUS))] != '1'
		&& game->parsing->map[(int)((new_pos.y
				- COLLISION_RADIUS))][map_x] != '1'
		&& game->parsing->map[(int)((new_pos.y
				+ COLLISION_RADIUS))][map_x] != '1' && moved)
	{
		player->pos = new_pos;
	}
	player->plane = calculate_plane(player->dir);
	game->player = player;
	return (moved);
}

void	listen_events(t_game *game)
{
	mlx_hook(game->mlx->win, 33, 0L, close_window, game);
	mlx_hook(game->mlx->win, 2, 1L << 0, key_press, game);
	mlx_hook(game->mlx->win, 3, 1L << 1, key_release, game);
	mlx_hook(game->mlx->win, MotionNotify,
		PointerMotionMask, handle_mouse, game);
}
