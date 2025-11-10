/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohdahma <mohdahma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 12:52:19 by mohdahma          #+#    #+#             */
/*   Updated: 2025/11/08 16:05:36 by mohdahma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void	init_img_clean(t_img *img)
{
	img->img = NULL;
	img->addr = NULL;
	img->bits_per_pixel = 0;
	img->line_length = 0;
	img->endian = 0;
	img->width = 0;
	img->height = 0;
}

void	get_txt_index(t_texture *texture, t_ray ray, int *index)
{
	(void)texture;
	if (ray.side == 0)
	{
		if (ray.dir.x > 0)
			*index = EAST;
		else
			*index = WEST;
	}
	else
	{
		if (ray.dir.y > 0)
			*index = SOUTH;
		else
			*index = NORTH;
	}
}

int		*xpm_to_buffer(t_game *game, t_texture *txtr, t_mlx *mlx, char *path);
void	update_texture(t_game *game, t_ray *ray, size_t x);
int		close_window(t_game *game);

void	init(t_tex_info *info, t_game *game)
{
	char	**buff;

	buff = ft_splits(game->parsing->elemets[0]);
	info->north = ft_strdup(buff[1]);
	freedouble(buff);
	buff = ft_splits(game->parsing->elemets[1]);
	info->south = ft_strdup(buff[1]);
	freedouble(buff);
	buff = ft_splits(game->parsing->elemets[2]);
	info->west = ft_strdup(buff[1]);
	freedouble(buff);
	buff = ft_splits(game->parsing->elemets[3]);
	info->east = ft_strdup(buff[1]);
	freedouble(buff);
}

void	setup_textures(t_game *game, t_texture *textrs, t_mlx *mlx)
{
	textrs->textures = ft_calloc(4, sizeof(t_img_wh));
	if (!textrs->textures)
		exit(close_window(game));
	init(&textrs->tex_info, game);
	textrs->index = NORTH;
	textrs->textures[NORTH].buffer = xpm_to_buffer(game, textrs, mlx,
			textrs->tex_info.north);
	textrs->index = SOUTH;
	textrs->textures[SOUTH].buffer = xpm_to_buffer(game, textrs, mlx,
			textrs->tex_info.south);
	textrs->index = EAST;
	textrs->textures[EAST].buffer = xpm_to_buffer(game, textrs, mlx,
			textrs->tex_info.east);
	textrs->index = WEST;
	textrs->textures[WEST].buffer = xpm_to_buffer(game, textrs, mlx,
			textrs->tex_info.west);
	free(textrs->tex_info.north);
	free(textrs->tex_info.south);
	free(textrs->tex_info.east);
	free(textrs->tex_info.west);
	game->texture = textrs;
}
