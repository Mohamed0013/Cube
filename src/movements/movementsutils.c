#include "shared.h"

int	free_mlx(t_mlx *mlx)
{
	if (mlx->win)
		mlx_destroy_window(mlx->mlx, mlx->win);
	if (mlx->mlx)
	{
		mlx_destroy_display(mlx->mlx);
		free(mlx->mlx);
	}
	free(mlx);
	return (0);
}

void	free_texture(t_texture *tex)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (tex->textures)
			free(tex->textures[i].buffer);
		i++;
	}
	free(tex->textures);
	i = 0;
	if (tex->screen_pixels)
	{
		while (i < HEIGHT)
		{
			if (tex->screen_pixels[i])
			{
				free(tex->screen_pixels[i]);
			}
			i++;
		}
		free(tex->screen_pixels);
	}
	free(tex);
}

void	free_data(void)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		free(data()->elemets[i]);
		i++;
	}
	freefile(data()->map);
}

int	close_window(t_game *game)
{
	free_mlx(game->mlx);
	free(game->player);
	free_texture(game->texture);
	free_data();
	exit(0);
}
