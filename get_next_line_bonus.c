/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoursou <asoursou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 14:56:36 by asoursou          #+#    #+#             */
/*   Updated: 2019/10/13 17:12:34 by asoursou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "get_next_line_bonus.h"

static t_file	*search_file(t_file **l, int fd)
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
	{
		if (p)
			p->next = f->next;
		else
			*l = NULL;
	}
	else if (!read(fd, NULL, 0) && (f = malloc(sizeof(t_file))))
	{
		f->buf = NULL;
		f->fd = fd;
		f->next = NULL;
	}
	return (f);
}

static int		join_line(t_file *f, char **line, char *b, int freeb)
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
	}
	else
		*line = ft_strdup(b);
	if (n)
		f->buf = (b[n]) ? ft_strdup(b + n) : NULL;
	else
		f->buf = *line;
	if (freeb)
		free(b);
	return (n > 0);
}

static int		read_line(t_file *f, char **line)
{
	char	buf[BUFFER_SIZE + 1];
	int		n;

	if (!(f->buf && *ft_strchrnul(f->buf, '\n')))
	{
		while ((n = read(f->fd, buf, BUFFER_SIZE)) > 0)
		{
			buf[n] = '\0';
			if (join_line(f, line, buf, 0))
				return (1);
		}
		if (n < 0)
		{
			if (f->buf)
			{
				free(f->buf);
				f->buf = NULL;
			}
			*line = NULL;
			return (-1);
		}
	}
	return (f->buf && join_line(f, line, f->buf, 1));
}

int			get_next_line(const int fd, char **line)
{
	static t_file	*l = NULL;
	t_file			*f;
	int				r;

	if (fd < 0 || !(f = search_file(&l, fd)))
		return (-1);
	if ((r = read_line(f, line)) < 1)
		free(f);
	else
	{
		f->next = l;
		l = f;
	}
	return (r);
}
