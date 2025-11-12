/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohdahma <mohdahma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 12:51:15 by mohdahma          #+#    #+#             */
/*   Updated: 2025/11/12 15:13:36 by mohdahma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shared.h"

void	setup_scene(t_game *game)
{
	t_img	img;

	init_img_clean(&img);
	img.img = mlx_new_image(game->mlx->mlx, WIDTH, HEIGHT);
	img.addr = (int *)mlx_get_data_addr(img.img, &img.bits_per_pixel,
			&img.line_length, &img.endian);
	game->current_scene = img;
	draw_floor_ceil(game);
}

void	init_mlx_struct(t_game *game)
{
	game->mlx->mlx = mlx_init();
	if (!game->mlx->mlx)
		exit(close_window(game));
	game->mlx->win = mlx_new_window(game->mlx->mlx, WIDTH, HEIGHT, "Cub3D");
	if (!game->mlx->win)
		exit(close_window(game));
	game->mlx->width = WIDTH;
	game->mlx->height = HEIGHT;
	ft_bzero(game->player, sizeof(t_player));
	ft_bzero(game->texture, sizeof(t_texture));
	game->player->mouse_active = 0;
	game->player->last_mouse_x = WIDTH / 2;
}

void	mlx(void)
{
	t_game(game) = {data(), malloc(sizeof(t_mlx)), malloc(sizeof(t_player)),
	malloc(sizeof(t_texture)), {0}, 0};
	init_mlx_struct(&game);
	get_player_pos_and_ang(&game);
	setup_textures(&game, game.texture, game.mlx);
	render_game(&game);
	listen_events(&game);
	mlx_loop_hook(game.mlx->mlx, render, &game);
	mlx_loop(game.mlx->mlx);
}
