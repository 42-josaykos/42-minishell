/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 11:51:53 by jonny             #+#    #+#             */
/*   Updated: 2020/11/30 11:57:02 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "../libft/libft.h"

int main(int argc, char **argv)
{
	int		ret;
	char	*line;
	int 	fd;

	line = NULL;

	if (argc >= 2)
		fd = open(argv[1], O_RDONLY);
	else
		fd = 0;

	while ((ret = get_next_line(fd, &line)) > 0)
	{
		ft_printf("%s\n", line);
		free(line);
		line = NULL;
	}
	if (fd != 0)
		close(fd);
	return (0);
}
