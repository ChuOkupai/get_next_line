/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoursou <asoursou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 14:56:36 by asoursou          #+#    #+#             */
/*   Updated: 2019/10/03 20:14:04 by asoursou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"

static int	join_line(t_list *f, char **line, char *b, int freeb)
{
	int n;

	if (b[n = ft_strchrnul(b, '\n') - b] == '\n')
		b[n++] = '\0';
	else if (b != f->content)
		n = 0;
	if (b != f->content)
	{
		*line = ft_strjoin(((f->content) ? f->content : ""), b);
		if (f->content)
			free(f->content);
	}
	else
		*line = ft_strdup(b);
	if (n)
		f->content = (b[n]) ? ft_strdup(b + n) : NULL;
	else
		f->content = *line;
	if (freeb)
		free(b);
	return (n > 0);
}

static int	read_line(t_list *f, char **line)
{
	char	buf[BUFF_SIZE + 1];
	int		n;

	if (!(f->content && ft_strchr(f->content, '\n')))
	{
		while ((n = read(f->content_size, buf, BUFF_SIZE)) > 0)
		{
			buf[n] = '\0';
			if (join_line(f, line, buf, 0))
				return (1);
		}
		if (n < 0)
		{
			if (f->content)
				ft_memdel((void**)&f->content);
			*line = NULL;
			return (-1);
		}
	}
	return (f->content && join_line(f, line, f->content, 1));
}

int			get_next_line(const int fd, char **line)
{
	static t_list	*l = NULL;
	t_list			*f;
	t_list			*prev;
	int				r;

	if (fd < 0)
		return (-1);
	prev = NULL;
	f = l;
	while (f && f->content_size != (size_t)fd)
	{
		prev = f;
		f = f->next;
	}
	if (f)
		(prev) ? (prev->next = f->next) : (l = NULL);
	else if (!read(fd, NULL, 0) && (f = ft_lstnew(NULL, 0)))
		f->content_size = fd;
	else
		return (-1);
	((r = read_line(f, line)) < 1) ? free(f) : ft_lstadd(&l, f);
	return (r);
}
