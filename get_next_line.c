/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoursou <asoursou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 14:56:36 by asoursou          #+#    #+#             */
/*   Updated: 2019/09/15 15:03:59 by asoursou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"

static int		fill_buffer(t_file *f, char **line)
{
	char *b;

	b = f->cur;
	if ((f->cur = ft_strchr(f->cur, '\n')))
		*f->cur++ = '\0';
	if (*line)
	{
		b = ft_strjoin(*line, b);
		free(*line);
		*line = b;
	}
	else
		*line = ft_strdup(b);
	return (!f->cur);
}

static int		read_line(t_file *f, char **line)
{
	ssize_t n;

	*line = NULL;
	n = 1;
	while (n && fill_buffer(f, line)
		&& (n = read(f->fd, f->buf, BUFF_SIZE)) >= 0)
	{
		f->buf[n] = '\0';
		f->cur = f->buf;
	}
	(n > 0 || (!n && **line)) ? n = 1 : ft_memdel((void**)line);
	return (n);
}

int				get_next_line(const int fd, char **line)
{
	static t_file f = { 0 };

	if (f.fd != fd)
	{
		f.buf[0] = '\0';
		f.cur = f.buf;
		f.fd = fd;
	}
	return (read_line(&f, line));
}
