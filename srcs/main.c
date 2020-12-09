/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <jonny@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 11:51:53 by jonny             #+#    #+#             */
/*   Updated: 2020/12/09 16:23:00 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

/*
** Prints a welcome message.
** TODO: Initialize environment variables here (PATH).
*/

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

/*
** Create a child process and execute the command in it. Parent process waits
** the child process to finish.
*/

void	exec_cmd(char *str)
{
	char	*args[2];
	char 	buf[1000];
	pid_t	p1;

	ft_strlcpy(buf, "./", 3);
	args[0] = ft_strcat(buf, str);
	args[1] = NULL;
	p1 = fork();
	if (p1 < 0)
	{
		ft_printf("Cannot execute child process.\n");
		exit(-1);
	}
	if (p1 == 0)
	{
		execve(args[0], args, NULL);
		exit(0);
	}
	wait(NULL);
}

/*
** Infinite loop that call get_input, a function printing a command prompt and
** waiting for an input.
** TODO: Need to call functions for parsing the input string
*/

int		main(int argc, char **argv)
{
	char input[MAXCHAR];
	int ret;

	(void)argv;
	ft_memset(input, '0', sizeof(input));
	if (argc < 2)
	{
		init_msh();
		while (1)
		{
			get_input(input);
			ret = parse_cmdline(input);
			if (ret == 1)
				break ;
			else if (ret == 2)
				exec_cmd(input);
		}
	}
	else
		printf("Usage: just ./minishell with no arguments.\n");
	return (EXIT_SUCCESS);
}
