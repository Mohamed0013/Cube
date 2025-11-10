/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohdahma <mohdahma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 12:52:40 by mohdahma          #+#    #+#             */
/*   Updated: 2025/11/08 12:52:41 by mohdahma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void	update_texture(t_game *game, t_ray *ray, size_t x)
{
	t_texture		*texture;
	unsigned int	color;

	int (y), (index);
	texture = game->texture;
	get_txt_index(texture, *ray, &index);
	texture->tex_info.x = (int)(ray->wall_x * texture->textures[index].width);
	int (z) = texture->tex_info.x;
	int (h) = texture->textures[index].height;
	if ((ray->side == 0 && ray->dir.x > 0) || (ray->side == 1
			&& ray->dir.y < 0))
		z = texture->textures[index].width - z - 1;
	texture->tex_info.step = 1.0 * h / ray->line_height;
	texture->tex_info.pos = (ray->draw_start - HEIGHT / 2 + ray->line_height
			/ 2) * texture->tex_info.step;
	y = ray->draw_start;
	while (y <= ray->draw_end)
	{
		texture->tex_info.y = (int)texture->tex_info.pos & (h - 1);
		texture->tex_info.pos += texture->tex_info.step;
		color = texture->textures[index].buffer[h * texture->tex_info.y + z];
		color = rgb_to_uint(apply_shading(clr_to_rgb(color), ray->wall_dist));
		set_pixel_image(&game->current_scene, x, y, color);
		y++;
	}
}

static void	ex(t_game *game, t_texture *txtr, char *s)
{
	exit(ftx(txtr) + (printf("%s\n", s) + close_window(game)));
}

int	*xpm_to_buffer(t_game *game, t_texture *txtr, t_mlx *mlx, char *path)
{
	int		*buffer;
	t_img	img;

	img.img = mlx_xpm_file_to_image(mlx->mlx, path, &img.width, &img.height);
	if (!img.img || img.width != img.height)
		ex(game, txtr, "Error in img.img mlx");
	img.addr = (int *)mlx_get_data_addr(img.img, &img.bits_per_pixel,
			&img.line_length, &img.endian);
	if (!img.addr)
		ex(game, txtr, "Error in img.addr mlx ");
	buffer = ft_calloc(img.width * img.height, sizeof(*buffer));
	if (!buffer)
		ex(game, txtr, "Calloc Faild ");
	ft_memcpy(buffer, img.addr, img.width * img.height * sizeof(*buffer));
	txtr->textures[txtr->index].width = img.width;
	txtr->textures[txtr->index].height = img.height;
	mlx_destroy_image(mlx->mlx, img.img);
	return (buffer);
}
