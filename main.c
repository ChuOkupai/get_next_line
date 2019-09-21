/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoursou <asoursou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 23:56:43 by asoursou          #+#    #+#             */
/*   Updated: 2019/09/21 14:07:59 by asoursou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <fcntl.h>
#include <get_next_line.h>
#include <stdlib.h>
#include <unistd.h>

int	main(int argc, char **argv)
{
	char	*s;
	int		fd;

	if (argc == 2 && (fd = open(argv[1], O_RDONLY)) > 0)
	{
		while (get_next_line(fd, &s) > 0)
		{
			ft_putendl(s);
			free(s);
		}
		close(fd);
	}
	return (0);
}
