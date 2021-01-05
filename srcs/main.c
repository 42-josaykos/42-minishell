/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <jonny@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 11:51:53 by jonny             #+#    #+#             */
/*   Updated: 2021/01/04 11:40:25 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"
#include <fcntl.h>

/*
** Prints a welcome message.
** Create a list of env variables.
** TODO: Need to handle mutliple variables in the config file (.mshrc)
*/

void	init_msh(t_env **env_lst)
{
	int		fd;

	ft_printf("Welcome to minishell !\nCtrl-C or \"exit\" to quit.\n");
	fd = open(".mshrc", O_RDWR);
	init_path(fd, env_lst);
	close(fd);
}

int	get_input(char *input)
{
	char	*line;

	line = NULL;
	ft_printf("minishell $ ");
	get_next_line(0, &line);
	ft_strlcpy(input, line, MAXCHAR);
	free(line);
	return (0);
}

/*
** Infinite loop that call get_input, a function printing a command prompt and
** waiting for an input.
** TODO: Need to call functions for parsing the input string
*/

void	main_loop(t_env *env_lst)
{
	char	input[MAXCHAR];
	char	*cmdargs[100];
	int		ret;

	while (1)
	{
		get_input(input);
		ret = parse_cmdline(env_lst, input, cmdargs);
		if (ret == EXIT)
			break ;
		else if (ret == EXPORT)
		{
			export_env(&env_lst, "testkey", "testvalue");
			ft_printf("env var testkey=testvalue added to the env list.\n");
		}
		else if (ret == CD)
			cd(cmdargs[1]);
	}
}

int	main(int argc, char **argv)
{
	t_env	*env_lst;

	(void)argv;
	env_lst = NULL;
	if (argc < 2)
	{
		init_msh(&env_lst);
		main_loop(env_lst);
	}
	else
		printf("Usage: just ./minishell with no arguments.\n");
	free_env_lst(&env_lst);
	return (EXIT_SUCCESS);
}
