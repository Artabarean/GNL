/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabarea <atabarea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 10:10:48 by alex              #+#    #+#             */
/*   Updated: 2025/02/20 11:50:16 by atabarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*free_str(char	*s1, char *s2)
{
	free(s1);
	free(s2);
	return (NULL);
}

static char	*read_line(int fd, char *remainder)
{
	char	*buffer;
	char	*temp;
	int		bytes_read;

	if (!remainder)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (free_str(remainder, buffer));
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read < 0 || (bytes_read == 0 && !*remainder))
		return (free_str(remainder, buffer));
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		temp = ft_strjoin(remainder, buffer);
		free(remainder);
		if (!temp)
			return (free(buffer), NULL);
		remainder = temp;
		if (ft_strchr(remainder, '\n'))
			break ;
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	return (free(buffer), remainder);
}

static char	*proc_nl(char *remainder, char **new_remainder, char *newpos)
{
	char	*aux;
	size_t	len;

	len = newpos - remainder + 1;
	aux = malloc(sizeof(char) * (len + 1));
	if (!aux)
	{
		free(remainder);
		return (NULL);
	}
	ft_strlcpy(aux, remainder, len + 1);
	*new_remainder = ft_strdup(newpos + 1);
	if (!(*new_remainder))
		return (free_str(remainder, aux));
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
			return (free(remainder), NULL);
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