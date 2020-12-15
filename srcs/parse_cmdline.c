/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmdline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <jonny@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 10:22:20 by jonny             #+#    #+#             */
/*   Updated: 2020/12/15 10:37:16 by jonny            ###   ########.fr       */
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

int		parse_cmdline(char *input)
{
	int		i;
	char	*cmds_list[4];

	i = 0;
	cmds_list[0] = "pwd";
	cmds_list[1] = "echo";
	cmds_list[2] = "cd";
	cmds_list[3] = NULL;
	if (ft_strncmp(input, "exit", 4) == 0)
		return (1);
	else if (ft_strncmp(input, "export", 4) == 0)
		return (3);
	else if (ft_strlen(input) != 0)
	{
		while (cmds_list[i])
		{
			if (ft_strncmp(input, cmds_list[i], ft_strlen(cmds_list[i])) == 0)
				return (2);
			i++;
		}
		ft_printf("msh: %s: command not found\n", input);
	}
	return (0);
}
