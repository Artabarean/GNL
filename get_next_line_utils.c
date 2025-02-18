/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabarea <atabarea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 09:46:25 by atabarea          #+#    #+#             */
/*   Updated: 2025/02/13 09:46:25 by atabarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	char	*memrsv;

	i = 0;
	if (!s1 || !s2)
		return (NULL);
	memrsv = malloc((ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (memrsv == NULL)
		return (NULL);
	while (*s1 != '\0')
	{
		memrsv[i] = *s1;
		s1++;
		i++;
	}
	while (*s2 != '\0')
	{
		memrsv[i] = *s2;
		s2++;
		i++;
	}
	memrsv[i] = '\0';
	return (memrsv);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	srcsize;

	if (!src)
		return (0);
	srcsize = ft_strlen(src);
	if (!dst || size == 0)
		return (srcsize);
	i = 0;
	while (i < (size - 1) && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (srcsize);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	if ((char)c == '\0' && s[i] == (char)c)
		return ((char *)&s[i]);
	return (NULL);
}

char	*ft_strdup(const char *s)
{
	char	*clone;
	size_t	len;
	size_t	i;

	i = 0;
	len = ft_strlen(s);
	clone = (char *)malloc(len + 1);
	if (clone == NULL)
		return (NULL);
	while (i < len)
	{
		clone[i] = *s;
		s++;
		i++;
	}
	clone[i] = '\0';
	return (clone);
}
