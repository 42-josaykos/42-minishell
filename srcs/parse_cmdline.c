/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmdline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <jonny@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 10:22:20 by jonny             #+#    #+#             */
/*   Updated: 2020/12/17 15:52:53 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

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

int		parse_cmdline(t_env *env_lst, char *input)
{
	int		i;
	char	filepath[MAXCHAR];
	t_env	*tmp;

	i = 0;
	tmp = env_lst;
	if (ft_strncmp(input, "exit", 4) == 0)
		return (1);
	else if (ft_strncmp(input, "export", 6) == 0)
		return (2);
	else if (ft_strncmp(input, "cd", 2) == 0)
		return (3);
	while (tmp)
	{
		if (ft_strncmp(tmp->key, "path", 4) == 0)
		{
			read_path(tmp, filepath);
			ft_strcat(filepath, input);
			if (file_exists(filepath) == 0)
			{
				exec_cmd(filepath);
				return (0);
			}
		}
		tmp = tmp->next;
	}
	if (tmp == NULL)
	{
		printf("msh: %s: not found. Try command in system shell...\n", input);
		exec_syscmd(input);
	}
	return (0);
}
