/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabarea <atabarea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 10:10:48 by alex              #+#    #+#             */
/*   Updated: 2025/02/13 11:42:37 by atabarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_line(int fd, char *remainder)
{
	char	buffer[BUFFER_SIZE + 1];
	char	*temp;
	int		bytes_read;

	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read < 0)
	{
		free(remainder);
		return (NULL);
	}
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
	return (remainder);
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
			return (NULL);
	}
	remainder = read_line(fd, remainder);
	if (!remainder)
		return (NULL);
	line = store_line(remainder, &new_remainder);
	remainder = new_remainder;
	return (line);
}
