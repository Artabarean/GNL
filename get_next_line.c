/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabarea <atabarea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 10:10:48 by alex              #+#    #+#             */
/*   Updated: 2025/02/13 10:31:27 by atabarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_line(int fd, char *remainder)
{
	char	buffer[BUFFER_SIZE + 1];
	char	*temp;
	int		bytes_read;

	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		temp = ft_strjoin(remainder, buffer);
		if (!temp)
		{
			free(remainder);
			return (NULL);
		}
		free(remainder);
		remainder = temp;
		if (ft_strchr(remainder, '\n'))
			break ;
	}
	if (bytes_read < 0)
	{
		free(remainder);
		return (NULL);
	}
	return (remainder);
}

static char	*store_line(char *remainder, char **new_remainder)
{
	char	*aux;
	char	*newpos;
	size_t	len;

	if (!remainder)
		return (NULL);
	newpos = ft_strchr(remainder, '\n');
	if (newpos)
	{
		len = newpos - remainder + 1;
		aux = malloc(sizeof(char) * (len + 1));
		if (!aux)
			return (NULL);
		ft_strlcpy(aux, remainder, len + 1);
		*new_remainder = ft_strdup(newpos + 1);
		free(remainder);
	}
	else
	{
		aux = remainder;
		new_remainder = NULL;
	}
	return (aux);
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
		return (remainder = NULL);
	}
	if (!remainder)
	{
		remainder = ft_strdup("");
		if (!remainder)
			return (NULL);
	}
	remainder = read_line(fd, remainder);
	if (!remainder)
		return (NULL);
	line = store_line(remainder, &new_remainder);
	remainder = new_remainder;
	return (line);
}
