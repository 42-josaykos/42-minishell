/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <jonny@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 11:51:53 by jonny             #+#    #+#             */
/*   Updated: 2020/12/17 12:37:05 by jonny            ###   ########.fr       */
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

	ft_printf("Welcome to minishell (msh)!\nCtrl-C or \"exit\" to quit msh.\n");
	fd = open(".mshrc", O_RDWR);
	init_path(fd, env_lst);
	close(fd);
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
** Infinite loop that call get_input, a function printing a command prompt and
** waiting for an input.
** TODO: Need to call functions for parsing the input string
*/

int		main(int argc, char **argv)
{
	char	input[MAXCHAR];
	int		ret;
	t_env	*env_lst;

	(void)argv;
	env_lst = NULL;
	ft_memset(input, '0', sizeof(input));
	if (argc < 2)
	{
		init_msh(&env_lst);
		while (1)
		{
			get_input(input);
			ret = parse_cmdline(env_lst, input);
			if (ret == EXIT)
				break ;
			else if (ret == 2)
				exec_cmd(env_lst, input);
			else if (ret == 3)
			{
				export_env(&env_lst, "testkey", "testvalue");
				ft_printf("env var testkey=testvalue added to the env list.\n");
			}
			else if (ret == 4)
				cd("libft");
			else
				exec_syscmd(input);
		}
	}
	else
		printf("Usage: just ./minishell with no arguments.\n");
	free_env_lst(&env_lst);
	return (EXIT_SUCCESS);
}
