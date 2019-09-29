/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoursou <asoursou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 14:56:36 by asoursou          #+#    #+#             */
/*   Updated: 2019/09/29 11:01:46 by asoursou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"

static t_file	*searchfd(t_file **l, const int fd)
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
	else if (!read(fd, NULL, 0) && (f = (t_file*)malloc(sizeof(t_file))))
	{
		f->buf = ft_strnew(0);
		f->fd = fd;
	}
	return (f);
}

static int		readline(t_file *f, char **line)
{
	char	buf[BUFF_SIZE + 1];
	char	*b;
	int		n;

	*line = NULL;
	while (!ft_strchr(f->buf, '\n') && (n = read(f->fd, buf, BUFF_SIZE)) > 0)
	{
		buf[n] = '\0';
		b = f->buf;
		f->buf = ft_strjoin(f->buf, buf);
		free(b);
	}
	if (f->buf[n = ft_strchrnul(f->buf, '\n') - f->buf] == '\n')
		f->buf[n++] = '\0';
	*line = ft_strdup(f->buf);
	b = f->buf;
	if (n)
		f->buf = ft_strdup(f->buf + n);
	free(b);
	return (n > 0);
}

int				get_next_line(const int fd, char **line)
{
	static t_file	*l = NULL;
	t_file			*f;
	int				r;

	if (!(f = searchfd(&l, fd)))
		return (-1);
	if ((r = readline(f, line)) < 1)
	{
		free(f);
		ft_memdel((void**)line);
	}
	else
	{
		f->next = l;
		l = f;
	}
	return (r);
}
