/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 10:13:23 by alex              #+#    #+#             */
/*   Updated: 2025/02/03 10:16:56 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <stddef.h>
# ifndef BUFFER_SIZE
#	define BUFFER_SIZE 42
#endif

char    *get_next_line(int fd);
char    *ft_strjoin(char const *s1, char const *s2);
size_t  ft_strlen(const char *s);
char	*ft_strdup(const char *s);
char    *ft_strchr(const char *s, int c);

#endif
