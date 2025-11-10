#include "../../include/shared.h"

int	isallspace(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
		{
			return (0);
		}
		i++;
	}
	return (1);
}

void	charscheck(char *element, char **split)
{
	if (ft_strcmp(element, "NO") && ft_strcmp(element, "SO")
		&& ft_strcmp(element, "WE") && ft_strcmp(element, "EA")
		&& ft_strcmp(element, "C") && ft_strcmp(element, "F"))
	{
		printf("Error\nin map2");
		exit(freefile(split) + freeelement());
	}
}

void	fil_ele(char *element, char *line)
{
	if (!data()->elemets[0] && !ft_strcmp(element, "NO"))
		data()->elemets[0] = ft_strdup(line);
	else if (!data()->elemets[1] && !ft_strcmp(element, "SO"))
		data()->elemets[1] = ft_strdup(line);
	else if (!data()->elemets[2] && !ft_strcmp(element, "WE"))
		data()->elemets[2] = ft_strdup(line);
	else if (!data()->elemets[3] && !ft_strcmp(element, "EA"))
		data()->elemets[3] = ft_strdup(line);
	else if (!data()->elemets[4] && !ft_strcmp(element, "C"))
		data()->elemets[4] = ft_strdup(line);
	else if (!data()->elemets[5] && !ft_strcmp(element, "F"))
		data()->elemets[5] = ft_strdup(line);
}

int	checkmap(char *line)
{
	static int	index = 0;
	char		**split;
	int			i;

	i = 0;
	split = ft_splits(line);
	if (!split)
		return (0);
	if (index < 6)
	{
		if (split[1] == NULL)
			exit(freefile(split) + printf("Error\nin map1\n") + freeelement());
		charscheck(split[0], split);
		fil_ele(split[0], line);
	}
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
	if (index == 6)
		return (1);
	index++;
	return (5);
}

// this is a line that  caused a segv in mlx parts why  nour add it ?
		// if ((int)i == data()->map_hight - 1)
		// 	j++;
void	fix_map(void)
{
	char **const	s = data()->map;
	size_t			i;
	size_t			j;

	i = 0;
	while (s[i])
	{
		j = ft_strlen(s[i]);
		if (s[i][j - 1] == '\n')
			s[i][j - 1] = '\0';
		while (j < data()->longest)
		{
			s[i] = ft_strjoin(s[i], " ");
			j++;
		}
		s[i] = ft_strjoin(s[i], "\0");
		i++;
	}
	issurrendbywalls();
}
