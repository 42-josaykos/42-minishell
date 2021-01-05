/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmdline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <jonny@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 10:22:20 by jonny             #+#    #+#             */
/*   Updated: 2021/01/05 12:10:33 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

void	cmd_handler(t_env *env_lst, char *input)
{
	char	filepath[MAXCHAR];

	while (env_lst)
	{
		if (ft_strncmp(env_lst->key, "path", 4) == 0)
		{
			read_path(env_lst, filepath);
			ft_strcat(filepath, input);
			if (file_exists(filepath) == 0)
			{
				exec_cmd(filepath);
				break ;
			}
		}
		env_lst = env_lst->next;
	}
	if (env_lst == NULL)
	{
		printf("minishell: %s: not found. Try in system shell...\n", input);
		exec_syscmd(input);
	}
}

/*
** Check the input.
** Returns 1 if "exit".
** Returns 2 if "export" command (debug test).
** Returns 3 if "cd".
** Check each path directories for the executable and execute it. If doesn't
** exists try the command in the system shell (debug test).
** Prints "command not found" message and  returns 0 if invalid command, but
** don't print the message if input is an empty string.
*/

int	parse_cmdline(t_env *env_lst, char *input, char **args)
{
	int		i;

	(void)args;
	i = 0;
	if (ft_strncmp(input, "exit", 4) == 0)
		return (EXIT);
	else if (ft_strncmp(input, "export", 6) == 0)
		return (EXPORT);
	else if (ft_strncmp(input, "cd", 2) == 0)
		return (CD);
	cmd_handler(env_lst, input);
	return (0);
}
