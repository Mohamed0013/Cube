/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohdahma <mohdahma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 16:19:07 by mohdahma          #+#    #+#             */
/*   Updated: 2025/11/12 12:44:47 by mohdahma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void	handle_mouse2(t_player *player, t_game *game, int x)
{
	int		delta_x;
	double	rotation;

	delta_x = x - WIDTH / 2;
	if (delta_x != 0)
	{
		rotation = delta_x * 0.005;
		vec2_rotate(&player->dir, -rotation);
		vec2_normalized(&player->dir);
		player->angle = vec2_to_angle(player->dir);
		player->plane = calculate_plane(player->dir);
		player->is_moving = 1;
		mlx_mouse_move(game->mlx->mlx, game->mlx->win, WIDTH / 2, HEIGHT / 2);
	}
}

int	handle_mouse(int x, int y, t_game *game)
{
	t_player	*player;
	static int	initialized;

	(void)y;
	player = game->player;
	if (!player->mouse_active)
		return (0);
	if (!initialized)
	{
		player->last_mouse_x = WIDTH / 2;
		initialized = 1;
		mlx_mouse_move(game->mlx->mlx, game->mlx->win, WIDTH / 2, HEIGHT / 2);
		return (0);
	}
	handle_mouse2(player, game, x);
	return (0);
}

void	toggle_mouse(t_game *game)
{
	static int	first_toggle;

	first_toggle = 1;
	if (!game || !game->player || !game->mlx || !game->mlx->win)
		return ;
	if (first_toggle)
	{
		game->player->mouse_active = 0;
		first_toggle = 0;
	}
	game->player->mouse_active = !game->player->mouse_active;
	if (game->player->mouse_active)
	{
		mlx_mouse_hide(game->mlx->mlx, game->mlx->win);
		game->player->last_mouse_x = WIDTH / 2;
		mlx_mouse_move(game->mlx->mlx, game->mlx->win, WIDTH / 2, HEIGHT / 2);
	}
	else
		mlx_mouse_show(game->mlx->mlx, game->mlx->win);
	game->player->is_moving = 1;
}
