#include "../../include/shared.h"

int	check_size(char **c, char **f)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	if (!c || !f)
		return (0);
	while (f[i])
	{
		i++;
	}
	while (c[j])
	{
		j++;
	}
	if (i != 3 || j != 3)
		return (0);
	return (1);
}

void	isdupchars(void)
{
	int (i), (j), (c);
	i = 0;
	c = 0;
	while (i < data()->lines)
	{
		if (data()->file[i])
		{
			j = 0;
			while (data()->file[i][j])
			{
				if (data()->file[i][j] == 'N' || data()->file[i][j] == 'S'
					|| data()->file[i][j] == 'E' || data()->file[i][j] == 'W')
				{
					c++;
					data()->pos[0] = j;
					data()->pos[1] = i;
				}
				j++;
			}
		}
		i++;
	}
	if (c != 1)
		exit(freefile(NULL) + freeelement() + printf("Error\nin map\n"));
}

void	copymap(void)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	data()->map = malloc(sizeof(char *) * (data()->lines + 1));
	if (!data()->map)
		exit(freefile(NULL) + freeelement());
	while (i < data()->lines)
	{
		if (data()->file[i])
		{
			data()->map[j] = ft_strdup(data()->file[i]);
			data()->map_hight++;
			if (!data()->map[j])
				exit(freefile(data()->map) + freeelement());
			j++;
		}
		i++;
	}
	data()->map[j] = NULL;
}

void	issurrendbywalls(void)
{
	int (j), (i) = fixe_file();
	while (++i < data()->lines)
	{
		if (data()->file[i])
		{
			j = -1;
			while (data()->file[i][++j])
			{
				if (data()->file[i][j] == '0' || data()->file[i][j] == 'N'
					|| data()->file[i][j] == 'S' || data()->file[i][j] == 'E'
					|| data()->file[i][j] == 'W')
				{
					if (!i || !j || !data()->file[i - 1] || !data()->file[i + 1]
						|| data()->file[i][j + 1] == ' ' || data()->file[i][j
						- 1] == ' ' || data()->file[i + 1][j] == ' '
						|| data()->file[i - 1][j] == ' ' || data()->file[i][j
						+ 1] == '\n' || data()->file[i][j - 1] == '\n'
						|| data()->file[i + 1][j] == '\n' || data()->file[i
						- 1][j] == '\n')
						exit(freefile(data()->map) + freeelement()
							+ printf("Error\nin map %d %d\n", i, j));
				}
			}
		}
	}
}
