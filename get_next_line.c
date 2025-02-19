/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 10:10:48 by alex              #+#    #+#             */
/*   Updated: 2025/02/19 11:26:57 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*free_str(char	*str)
{
	free(str);
	return (NULL);
}

static char	*read_line(int fd, char *remainder)
{
	char	buffer[BUFFER_SIZE + 1];
	char	*temp;
	int		bytes_read;

	if (!remainder)
		return (NULL);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read < 0)
		return (free_str(remainder));
	if (bytes_read == 0 && remainder[0] == '\0')
		return (free_str(remainder));
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		temp = ft_strjoin(remainder, buffer);
		if (!temp)
			return (free_str(remainder));
		free(remainder);
		remainder = temp;
		if (ft_strchr(remainder, '\n'))
			break ;
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	return (remainder);
}

static char	*proc_nl(char *remainder, char **new_remainder, char *newpos)
{
	char	*aux;
	size_t	len;

	len = newpos - remainder + 1;
	aux = malloc(sizeof(char) * (len + 1));
	if (!aux)
		return (free_str(remainder));
	ft_strlcpy(aux, remainder, len + 1);
	*new_remainder = ft_strdup(newpos + 1);
	if (!(*new_remainder))
	{
		free(remainder);
		free(aux);
		return (NULL);
	}
	free(remainder);
	return (aux);
}

static char	*store_line(char *remainder, char **new_remainder)
{
	char	*aux;
	char	*newpos;

	if (!remainder)
		return (NULL);
	newpos = ft_strchr(remainder, '\n');
	if (!newpos)
	{
		if (*remainder == '\0')
		{
			free(remainder);
			*new_remainder = NULL;
			return (NULL);
		}
		aux = remainder;
		*new_remainder = NULL;
		return (aux);
	}
	return (proc_nl(remainder, new_remainder, newpos));
}

char	*get_next_line(int fd)
{
	static char	*remainder;
	char		*line;
	char		*new_remainder;

	new_remainder = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)
	{
		free(remainder);
		remainder = NULL;
		return (NULL);
	}
	if (!remainder)
	{
		remainder = ft_strdup("");
		if (!remainder)
			return (free_str(remainder));
	}
	remainder = read_line(fd, remainder);
	if (!remainder)
		return (remainder = NULL);
	line = store_line(remainder, &new_remainder);
	remainder = new_remainder;
	return (line);
}

// #include <stdio.h>
// int main()
// {
// 	int	fd = open("test.txt", O_RDONLY);
// 	if (fd == -1)
// 	{
// 		perror("Error opening file");
// 		return (1);
// 	}
// 	char *line;
// 	while ((line = get_next_line(fd)) != NULL)
// 	{
// 		printf("%s\n", line);
// 		free(line);
// 	}
//     close(fd);
//     return (0);
// }