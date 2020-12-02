/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <jonny@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 11:51:53 by jonny             #+#    #+#             */
/*   Updated: 2020/12/02 16:04:17 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

void	init_msh(void)
{
	ft_printf("Welcome to minishell (msh)!\nCtrl-C or \"exit\" to quit msh.\n");
}

int		get_input(char *input)
{
	char *line;

	line = NULL;
	ft_printf("$ ");
	get_next_line(0, &line);
	ft_strlcpy(input, line, MAXCHAR);
	free(line);
	return (0);
}

void	exec_cmd(void)
{
	char *args[2];
	pid_t p1;

	args[0] = "./pwd";
	args[1] = NULL;
	p1 = fork();
	if (p1 < 0)
		ft_printf("Cannot execute child process.\n");
	if (p1 == 0)
		execve("./pwd", args, NULL);
	wait(NULL);
}

int		main(int argc, char **argv)
{
	char input[MAXCHAR];

	(void)argv;
	if (argc < 2)
	{
		init_msh();
		while (1)
		{
			get_input(input);
			if (ft_strncmp(input, "exit", 4) == 0)
				break ;
			else if (ft_strncmp(input, "pwd", 3) == 0)
				exec_cmd();
			else
				ft_printf("msh: %s: command not found\n", input);
		}
	}
	else
		printf("Usage: just ./minishell with no arguments.\n");
	return (EXIT_SUCCESS);
}
