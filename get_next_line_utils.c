/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoursou <asoursou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 16:03:52 by asoursou          #+#    #+#             */
/*   Updated: 2019/10/13 17:13:31 by asoursou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "get_next_line_bonus.h"

static void		*ft_memcpy(void *dst, const void *src, size_t n)
{
	while (n--)
		((unsigned char*)dst)[n] = ((unsigned char*)src)[n];
	return (dst);
}

static size_t	ft_strlen(const char *str)
{
	size_t i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char			*ft_strchrnul(const char *s, int c)
{
	while (*s && *s != (char)c)
		s++;
	return ((char*)s);
}

char			*ft_strdup(const char *s1)
{
	char	*d;
	size_t	n;

	n = ft_strlen(s1) + 1;
	if ((d = (char*)malloc(n * sizeof(char))))
		ft_memcpy(d, s1, n);
	return (d);
}

char			*ft_strjoin(char const *s1, char const *s2)
{
	char	*d;
	size_t	n1;
	size_t	n2;

	n1 = ft_strlen(s1);
	n2 = ft_strlen(s2) + 1;
	if ((d = (char*)malloc((n1 + n2) * sizeof(char))))
	{
		ft_memcpy(d, s1, n1);
		ft_memcpy(d + n1, s2, n2);
	}
	return (d);
}
