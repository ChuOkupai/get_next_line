/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoursou <asoursou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 23:56:43 by asoursou          #+#    #+#             */
/*   Updated: 2019/09/25 19:54:09 by asoursou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <get_next_line.h>
#include <stdlib.h>
#include <unistd.h>

void	close_all(int *f, int size)
{
	while (size--)
		close(f[size]);
}

int		open_all(int *f, int size, char **argv)
{
	int i;

	i =-1;
	while (++i < size)
		if ((f[i] = open(argv[i], O_RDONLY)) < 0)
		{
			close_all(f, i);
			return (-1);
		}
	return (0);
}

int		read_all(int *f, int size)
{
	char	*s;
	int		i;
	int		n;

	i = 0;
	n = 0;
	while (i < size)
	{
		if (f[i])
		{
			if (get_next_line(f[i], &s) > 0)
			{
				ft_putendl(s);
				free(s);
				n++;
			}
			else
			{
				close(f[i]);
				f[i] = 0;
			}
		}
		i++;
	}
	return (n);
}

int		main(int argc, char **argv)
{
	if (argc > 1)
	{
		int f[--argc];

		if (!open_all(f, argc, argv + 1))
			while (read_all(f, argc));
	}
	return (0);
}
