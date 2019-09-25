/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoursou <asoursou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 14:56:36 by asoursou          #+#    #+#             */
/*   Updated: 2019/09/25 20:55:51 by asoursou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"

static t_file	*create_file(t_file **l, const int fd)
{
	t_file *f;

	if ((f = (t_file*)malloc(sizeof(t_file))))
	{
		if ((f->buf = (char*)malloc((BUFF_SIZE + 1) * sizeof(char))))
		{
			f->buf[0] = '\0';
			f->cur = f->buf;
			f->fd = fd;
			f->next = *l;
			*l = f;
		}
		else
			ft_memdel((void**)&f);
	}
	return (f);
}

static t_file	*search_file(t_file **l, const int fd)
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
	if (!f)
		return (create_file(l, fd));
	if (p)
	{
		p->next = f->next;
		f->next = *l;
		*l = f;
	}
	return (f);
}

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
	int				r;
	static t_file	*l = NULL;
	t_file			*f;

	if (!(f = search_file(&l, fd)))
		return (-1);
	if ((r = read_line(f, line)) < 1)
	{
		l = l->next;
		free(f->buf);
		free(f);
	}
	return (r);
}
