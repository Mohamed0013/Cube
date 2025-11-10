#include "../../include/shared.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// char	*get_next_line(int fd)
// {
// 	int		byte;
// 	char	c;
// 	char	*str_buffer;
// 	int		i;

// 	if (fd < 0)
// 		return (NULL);
// 	i = 0;
// 	str_buffer = (char *)malloc(5000);
// 	if (!str_buffer)
// 		return (NULL);
// 	byte = read(fd, &c, 1);
// 	while (byte > 0)
// 	{
// 		str_buffer[i] = c;
// 		i++;
// 		if (c == '\n' || c == EOF)
// 			break ;
// 		byte = read(fd, &c, 1);
// 	}
// 	if (i == 0 || byte < 0)
// 		return (free(str_buffer), NULL);
// 	str_buffer[i] = '\0';
// 	return (str_buffer);
// }
size_t	get_longest_line(void)
{
	int	i;
	int	max;
	int	len;

	i = 0;
	max = 0;
	while (data()->map[i])
	{
		len = ft_strlen(data()->map[i]);
		if (len > max)
			max = len;
		i++;
	}
	return (max);
}

void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);
	if (ptr)
	{
		if (old_size > 0)
			ft_memcpy(new_ptr, ptr, old_size);
		free(ptr);
	}
	return (new_ptr);
}

char	*addzero(ssize_t i, ssize_t byte, char *str_buffer)
{
	if (i == 0 || byte < 0)
		return (free(str_buffer), NULL);
	str_buffer[i] = '\0';
	return (str_buffer);
}

char	*get_next_line(int fd)
{
	char	*str_buffer;
	char	c;

	long (byte), (i) = 0, (buffer_size) = 1;
	buffer_size = 1;
	str_buffer = (char *)malloc(buffer_size);
	if (!str_buffer)
		return (NULL);
	byte = read(fd, &c, 1);
	while (byte > 0)
	{
		if (i >= buffer_size - 1)
		{
			buffer_size++;
			str_buffer = ft_realloc(str_buffer, buffer_size - 1, buffer_size);
			if (!str_buffer)
				return (NULL);
		}
		str_buffer[i] = c;
		i++;
		if (c == '\n' || c == EOF)
			break ;
		byte = read(fd, &c, 1);
	}
	return (addzero(i, byte, str_buffer));
}
