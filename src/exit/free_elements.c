#include "shared.h"

int	freefile(char **tofree)
{
	int	i;

	i = 0;
	while (i < data()->lines)
	{
		free(data()->file[i]);
		i++;
	}
	close(data()->fd);
	free(data()->file);
	if (tofree == NULL)
		return (0);
	else
	{
		i = 0;
		while (tofree[i])
		{
			free(tofree[i]);
			i++;
		}
		free(tofree);
	}
	return (0);
}

void	ft_exit(char **floor, char **ceiling, char **toaoitc, char **toaoitf)
{
	freedouble(floor);
	freedouble(ceiling);
	freedouble(toaoitf);
	freedouble(toaoitc);
}

void	freedouble(char **str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
		{
			free(str[i]);
			i++;
		}
		free(str);
	}
}

void	free_2d_array(void ***array, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free((*array)[i]);
		i++;
	}
	if (*array)
	{
		free(*array);
		*array = NULL;
	}
}

int	ftx(t_texture *txxr)
{
	free(txxr->tex_info.north);
	free(txxr->tex_info.south);
	free(txxr->tex_info.east);
	free(txxr->tex_info.west);
	return (9);
}
