/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movementsutils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohdahma <mohdahma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 12:48:25 by mohdahma          #+#    #+#             */
/*   Updated: 2025/11/12 12:48:26 by mohdahma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shared.h"

void	handle_movement(t_player *player, t_vec2 *new_pos, int *moved)
{
	if (player->move_forward)
	{
		*new_pos = add_vec2(player->pos, vec2_scale(player->dir,
					player->move_speed));
		*moved = 1;
	}
	if (player->move_back)
	{
		*new_pos = vec2_sub_vec2(player->pos, vec2_scale(player->dir,
					player->move_speed));
		*moved = 1;
	}
	if (player->move_left)
	{
		*new_pos = vec2_sub_vec2(player->pos, vec2_scale(player->plane,
					player->move_speed));
		*moved = 1;
	}
	if (player->move_right)
	{
		*new_pos = add_vec2(player->pos, vec2_scale(player->plane,
					player->move_speed));
		*moved = 1;
	}
}

void	handle_rotation(t_player *player, int *moved)
{
	if (player->rotate == -1)
	{
		vec2_rotate(&player->dir, -player->rot_speed);
		player->angle = vec2_to_angle(player->dir);
		*moved = 1;
	}
	if (player->rotate == 1)
	{
		vec2_rotate(&player->dir, player->rot_speed);
		player->angle = vec2_to_angle(player->dir);
		*moved = 1;
	}
}
