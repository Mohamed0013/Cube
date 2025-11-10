#include "../../include/shared.h"

int	assigmnet(char *str)
{
	if (ft_strcmp(str, "NO") == 0)
		return (-3);
	else if (ft_strcmp(str, "SO") == 0)
		return (-4);
	else if (ft_strcmp(str, "WE") == 0)
		return (-5);
	else if (ft_strcmp(str, "EA") == 0)
		return (-6);
	else if (ft_strcmp(str, "F") == 0)
		return (-7);
	else if (ft_strcmp(str, "C") == 0)
		return (-8);
	return (0);
}

void	sameelemet(void)
{
	char	**str;

	int (i), (j) = 0;
	i = 33;
	while (j < 6)
	{
		str = ft_splits(data()->elemets[j]);
		if (str)
		{
			if (str[2])
				i += 100;
			i += assigmnet(str[0]);
		}
		freedouble(str);
		j++;
	}
	if (i != 0)
		exit(printf("Error\nmissing element") + freefile(NULL) + freeelement());
}

void	checkelements(void)
{
	int		i;
	char	**split;
	int		fd;

	i = 0;
	while (i < 4)
	{
		split = ft_splits(data()->elemets[i]);
		fd = open(split[1], O_RDONLY);
		if (fd == -1)
		{
			printf("Error\nin map13 %s-\n", split[1]);
			freedouble(split);
			exit(freefile(NULL) + freeelement());
		}
		freedouble(split);
		close(fd);
		i++;
	}
	copymap();
}

void	getcolor(void)
{
	char	**parsecolor[4];

	parsecolor[0] = ft_splits(data()->elemets[4]);
	parsecolor[1] = ft_splits(data()->elemets[5]);
	parsecolor[2] = ft_spitv(parsecolor[0][1]);
	parsecolor[3] = ft_spitv(parsecolor[1][1]);
	int (i) = -1;
	if (!check_size(parsecolor[2], parsecolor[3]))
	{
		ft_exit(parsecolor[0], parsecolor[1], parsecolor[2], parsecolor[3]);
		exit(printf("Error\nin map51\n") + freefile(NULL) + freeelement());
	}
	while (++i < 3)
	{
		data()->mapcolor[0][i] = ft_atoi(parsecolor[2][i]);
		data()->mapcolor[1][i] = ft_atoi(parsecolor[3][i]);
		if (data()->mapcolor[0][i] > 255 || data()->mapcolor[1][i] > 255
			|| data()->mapcolor[0][i] < 0 || data()->mapcolor[1][i] < 0)
		{
			ft_exit(parsecolor[0], parsecolor[1], parsecolor[2], parsecolor[3]);
			exit(printf("Error\nin map1\n") + freefile(NULL) + freeelement());
		}
	}
	ft_exit(parsecolor[0], parsecolor[1], parsecolor[2], parsecolor[3]);
	checkelements();
}

void	charsinmap(void)
{
	int (i), (j);
	i = 0;
	sameelemet();
	while (i < data()->lines)
	{
		if (data()->file[i])
		{
			j = -1;
			while (data()->file[i][++j])
			{
				if (data()->file[i][j] != ' ' && data()->file[i][j] != '1'
					&& data()->file[i][j] != '0' && data()->file[i][j] != 'N'
					&& data()->file[i][j] != 'S' && data()->file[i][j] != 'E'
					&& data()->file[i][j] != 'W' && data()->file[i][j] != '\n')
				{
					printf("Error\nin map3");
					exit(freefile(NULL) + freeelement());
				}
			}
		}
		i++;
	}
	isdupchars();
	getcolor();
}
