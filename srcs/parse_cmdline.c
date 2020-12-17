/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmdline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <jonny@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 10:22:20 by jonny             #+#    #+#             */
/*   Updated: 2020/12/17 12:31:14 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

/*
** Check the input.
** Returns 3 if "export" command (debug test).
** Returns 2 if this a valid command.
** Returns 1 if "exit".
** Prints "command not found" message and  returns 0 if invalid command, but
** don't print the message if input is an empty string.
*/

int		parse_cmdline(t_env *env_lst, char *input)
{
	int		i;
	char	filepath[MAXCHAR];

	i = 0;
	read_path(env_lst, filepath);
	ft_strcat(filepath, input);
	if (file_exists(filepath) == 0)
		return (2);
	else if (ft_strncmp(input, "exit", 4) == 0)
		return (1);
	else if (ft_strncmp(input, "export", 6) == 0)
		return (3);
	else if (ft_strncmp(input, "cd", 2) == 0)
		return (4);
	printf("msh: %s: command not found\n", input);
	return (0);
}
