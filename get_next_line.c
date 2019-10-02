/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoursou <asoursou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 14:56:36 by asoursou          #+#    #+#             */
/*   Updated: 2019/10/02 22:12:27 by asoursou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"

static t_file	*search_fd(t_file **l, const int fd)
{
	t_file *f;
	t_file *p;

	p = NULL;
	f = *l;
	while (f && f->fd != fd)
	{
		p = f;
		f = f->next;
	}
	if (f)
		(p) ? (p->next = f->next) : (*l = NULL);
	else if (!read(fd, NULL, 0) && (f = (t_file*)ft_memalloc(sizeof(t_file))))
		f->fd = fd;
	if (f)
		f->next = *l;
	return (f);
}

static int		join_line(t_file *f, char **line, char *b)
{
	int n;

	if (b[n = ft_strchrnul(b, '\n') - b] == '\n')
		b[n++] = '\0';
	else if (b != f->buf)
		n = 0;
	if (b != f->buf)
	{
		*line = ft_strjoin(((f->buf) ? f->buf : ""), b);
		if (f->buf)
			free(f->buf);
		if (n)
			f->buf = (b[n]) ? ft_strdup(b + n) : NULL;
		else
			f->buf = *line;
		return (n > 0);
	}
	*line = ft_strdup(b);
	f->buf = (b[n]) ? ft_strdup(b + n) : NULL;
	free(b);
	return (1);
}

static int		read_line(t_file *f, char **line)
{
	char	buf[BUFF_SIZE + 1];
	int		n;

	if (!(f->buf && ft_strchr(f->buf, '\n')))
	{
		while ((n = read(f->fd, buf, BUFF_SIZE)) > 0)
		{
			buf[n] = '\0';
			if (join_line(f, line, buf))
				return (1);
		}
		if (n < 0)
		{
			if (f->buf)
				ft_memdel((void**)&f->buf);
			*line = NULL;
			return (-1);
		}
	}
	return (f->buf && join_line(f, line, f->buf));
}

int				get_next_line(const int fd, char **line)
{
	static t_file	*l = NULL;
	t_file			*f;
	int				r;

	if (!(f = search_fd(&l, fd)))
		return (-1);
	r = read_line(f, line);
	(r < 1) ? free(f) : (l = f);
	return (r);
}
