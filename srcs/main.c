/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 11:51:53 by jonny             #+#    #+#             */
/*   Updated: 2020/11/30 13:23:02 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "../libft/libft.h"

void msh_loop(void)
{
	char *line;

	line = NULL;
	ft_printf("Welcome to minishell (msh)!\nCtrl-C or \"exit\" to quit msh.\n");
	while (1)
	{
		ft_printf("$ ");
		get_next_line(0, &line);
		if (ft_strncmp(line, "exit", 4) == 0)
			break ;
		ft_printf("%s\n", line);
		free(line);
		line = NULL;
	}
	free(line);
	line = NULL;
}

int main(int argc, char **argv)
{
	(void)argv;
	if (argc < 2)
		msh_loop();
	return EXIT_SUCCESS;
}
