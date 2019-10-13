/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoursou <asoursou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 14:56:36 by asoursou          #+#    #+#             */
/*   Updated: 2019/10/13 17:13:49 by asoursou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

typedef struct	s_file
{
	char			*buf;
	int				fd;
	struct s_file	*next;
}				t_file;

char			*ft_strchrnul(const char *s, int c);

char			*ft_strdup(const char *s1);

char			*ft_strjoin(char const *s1, char const *s2);

int				get_next_line(const int fd, char **line);

#endif
