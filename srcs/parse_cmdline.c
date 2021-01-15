/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmdline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <jonny@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 10:22:20 by jonny             #+#    #+#             */
/*   Updated: 2021/01/15 12:48:44 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

void	parse_args(char *str, char **args)
{
	int	i;

	i = 0;
	while (i < 100)
	{
		args[i] = ft_strsep(&str, " ");
		if (args[i] == NULL)
			break ;
		if (strlen(args[i]) == 0)
			i--;
		i++;
	}
}

/*
** Check the input.
** Returns 1 if "exit".
** Returns 2 if "export" command (debug test).
** Returns 3 if "cd".
** Check each path directories for the executable and execute it. If doesn't
** exists try the command in the system shell (debug test).
*/

int	parse_cmdline(t_env *env_lst, char *input, char **args, char **piped)
{
	check_pipe(input, args, piped);
	if (ft_strncmp(args[0], "exit", 4) == 0)
		return (EXIT);
	else if (ft_strncmp(args[0], "export", 6) == 0)
		return (EXPORT);
	else if (ft_strncmp(args[0], "cd", 2) == 0)
		return (CD);
	cmd_handler(env_lst, input);
	return (0);
}
