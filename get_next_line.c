/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoursou <asoursou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 14:56:36 by asoursou          #+#    #+#             */
/*   Updated: 2019/09/12 17:39:42 by asoursou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"

static char		*line_copy(t_file *f, char *line, size_t *len, size_t n)
{
	char *d;

	d = ft_strnew(*len + n);
	ft_memcpy(d, line, len);
	free(line);
	*len += n;
	if ((f->cursor += n) == BUFF_SIZE)
		f->cursor = 0;
	return (ft_strncat(d, f->buf, n));
}

static int		read_line(t_file *f, char **line)
{
	size_t	i;
	ssize_t	n;

	i = 0;
	if (!(t = ft_strchr(f->buf + f->cursor, '\n')))
		t = f->buf[BUFF_SIZE];
	if ((n = t - f->buf) < BUFF_SIZE)
	{
		*line = line_copy(f, *line, i, n);
		return (1);
	}
	n = 0;
	while ((n = read(f->fd, f->buf, BUFF_SIZE)) > 0)
	{
		ft_memprint(f->buf, n);
		printf("cur = %lu\n", n);
		*line = line_copy(f, *line, i, n);
	}
	if (n < 0)
	{
		ft_memdel((void**)line);
		return (-1);
	}
	return (n != 0);
}

int				get_next_line(const int fd, char **line)
{
	static t_file f = { 0 };

	if (f.fd != fd)
	{
		f.buf[0] = '\0';
		f.buf[BUFF_SIZE] = '\0';
		f.fd = fd;
		f.cursor = 0;
	}
	*line = ft_strnew(0);
	return (read_line(&f, line));
}
