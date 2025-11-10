/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohdahma <mohdahma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 12:51:15 by mohdahma          #+#    #+#             */
/*   Updated: 2025/11/08 12:51:16 by mohdahma         ###   ########.fr       */
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
	game->mlx->win = mlx_new_window(game->mlx->mlx, WIDTH, HEIGHT, "Cub3D_42");
	if (!game->mlx->win)
		exit(close_window(game));
	game->mlx->width = WIDTH;
	game->mlx->height = HEIGHT;
	ft_bzero(game->player, sizeof(t_player));
	ft_bzero(game->texture, sizeof(t_texture));
}

int	render_game(t_game *game)
{
	setup_scene(game);
	tmp_raycaster(game);
	mlx_put_image_to_window(game->mlx->mlx, game->mlx->win,
		game->current_scene.img, 0, 0);
	mlx_destroy_image(game->mlx->mlx, game->current_scene.img);
	return (0);
}

int	render(t_game *game)
{
	game->frame = 1.0 / 60.0;
	game->player->move_speed = game->frame * SPEED;
	game->player->rot_speed = game->frame * ROT_SPEED;
	game->player->is_moving = move_player(game);
	if (game->player->is_moving == 0)
		return (0);
	render_game(game);
	return (0);
}

void	start_mlx(void)
{
	t_game(game) = {data(), malloc(sizeof(t_mlx)), malloc(sizeof(t_player)),
	malloc(sizeof(t_texture)), {0}, 0};
	init_mlx_struct(&game);
	get_player_pos_and_dst(&game);
	setup_textures(&game, game.texture, game.mlx);
	render_game(&game);
	listen_events(&game);
	mlx_loop_hook(game.mlx->mlx, render, &game);
	mlx_loop(game.mlx->mlx);
}
