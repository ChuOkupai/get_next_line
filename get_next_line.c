/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoursou <asoursou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 14:56:36 by asoursou          #+#    #+#             */
/*   Updated: 2019/09/14 21:59:14 by asoursou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"

static int		read_line(t_file *f, char **line)
{
	char	*b;
	ssize_t	n;

	/*ft_memprint(f->buf, BUFF_SIZE);
	ft_putendl("cur:");
	ft_memprint(f->cur, ft_strlen(f->cur));*/
	if ((b = ft_strchr(f->cur, '\n')))
	{
		*b = '\0';
		n = b - f->cur;
		*line = ft_strdup(f->cur);
		f->cur = b + 1;
	}
	else
	{
		*line = ft_strdup(f->cur);
		n = BUFF_SIZE;
	}
	while (n == BUFF_SIZE && (n = read(f->fd, f->buf, BUFF_SIZE)) > 0)
	{
		f->buf[n] = '\0';
		if ((f->cur = ft_strchr(f->buf, '\n')))
		{
			*f->cur = '\0';
			n = f->cur++ - f->buf;
		}
		else
			f->cur = f->buf + BUFF_SIZE;
		if (n)
		{
			b = ft_strjoin(*line, f->buf);
			free(*line);
			*line = b;
		}
	}
	if (n < 1)
		ft_memdel((void**)line);
	if (n > 0)
		n = 1;
	return (n);
}

int				get_next_line(const int fd, char **line)
{
	static t_file f = { 0 };

	if (f.fd != fd)
	{
		ft_bzero(f.buf, BUFF_SIZE); // debug
		f.buf[0] = '\0';
		f.cur = f.buf;
		f.fd = fd;
	}
	*line = ft_strnew(0);
	return (read_line(&f, line));
}
