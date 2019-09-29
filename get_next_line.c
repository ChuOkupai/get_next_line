/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoursou <asoursou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 14:56:36 by asoursou          #+#    #+#             */
/*   Updated: 2019/09/29 18:22:23 by asoursou         ###   ########.fr       */
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
	else if ((f = (t_file*)ft_memalloc(sizeof(t_file))))
		f->fd = fd;
	if (f)
		f->next = *l;
	return (f);
}

static int		read_line(t_file *f, char **line)
{
	char	buf[BUFF_SIZE + 1];
	int		n;

	n = 0;
	while (!(f->buf && ft_strchr(f->buf, '\n'))
		&& (n = read(f->fd, buf, BUFF_SIZE)) > 0)
	{
		buf[n] = '\0';
		*line = ft_strjoin(((f->buf) ? f->buf : ""), buf);
		if (f->buf)
			free(f->buf);
		f->buf = *line;
	}
	if (n < 0)
	{
		if (f->buf)
			ft_memdel((void**)&f->buf);
		*line = NULL;
	}
	return (n);
}

int				get_next_line(const int fd, char **line)
{
	static t_file	*l = NULL;
	t_file			*f;
	char			*b;
	int				r;

	if (!(f = search_fd(&l, fd)) || read_line(f, line) < 0)
		return (-1);
	r = 0;
	if ((b = f->buf))
	{
		if (b[r = ft_strchrnul(b, '\n') - b] == '\n')
			b[r++] = '\0';
		*line = ft_strdup(b);
		f->buf = (b[r]) ? ft_strdup(b + r) : NULL;
		free(b);
	}
	else
		*line = NULL;
	(r < 1) ? free(f) : (l = f);
	return (r > 0);
}
