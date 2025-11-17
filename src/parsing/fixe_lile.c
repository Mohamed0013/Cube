/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fixe_lile.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-yag <moel-yag@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 10:45:18 by moel-yag          #+#    #+#             */
/*   Updated: 2025/11/17 10:45:19 by moel-yag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shared.h"

void	rt(void)
{
	int		i;
	size_t	j;

	j = 0;
	i = 0;
	while (i < data()->lines)
	{
		if (data()->file[i])
		{
			j = ft_strlen(data()->file[i]);
			if (j > data()->longest)
				data()->longest = j;
		}
		i++;
	}
}

int	fixe_file(void)
{
	char **const	s = data()->file;
	size_t			i;
	size_t			j;

	i = 0;
	while ((int)i < data()->lines)
	{
		if (data()->file[i])
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
		}
		i++;
	}
	return (-1);
}
