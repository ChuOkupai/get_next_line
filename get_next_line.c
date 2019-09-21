/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoursou <asoursou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 14:56:36 by asoursou          #+#    #+#             */
/*   Updated: 2019/09/21 14:37:33 by asoursou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"

static t_file	*find_file(t_list **l, const int fd)
{
	t_file f;
	t_list *e;

	e = *l;
	while (e && ((t_file*)e->content)->fd != fd)
		e = e->next;
	if (!e)
	{
		f.buf[0] = '\0';
		f.fd = fd;
		if (!(e = ft_lstnew(&f, sizeof(t_file))))
			return (NULL);
		((t_file*)e->content)->cur = ((t_file*)e->content)->buf;
		ft_lstadd(l, e);
	}
	return (e->content);
}

static void		remove_file(t_list **l, t_file *f)
{
	t_list *e;
	t_list *p;

	p = NULL;
	e = *l;
	while (e && (t_file*)e->content != f)
	{
		p = e;
		e = e->next;
	}
	if (p)
		p->next = e->next;
	else
		*l = e->next;
	free(e);
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
	static t_list	*l = NULL;
	t_file			*f;

	if (!(f = find_file(&l, fd)))
		return (-1);
	if ((r = read_line(f, line)) < 1)
		remove_file(&l, f);
	return (r);
}
