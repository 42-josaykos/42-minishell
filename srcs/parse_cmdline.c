/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmdline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 10:22:20 by jonny             #+#    #+#             */
/*   Updated: 2021/01/18 11:03:04 by jonny            ###   ########.fr       */
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

int	parse_cmdline(t_env *env_lst, t_cmd *cmd_lst, char *input)
{
	clear_previous_cmd(cmd_lst);
	if (check_pipe(input, cmd_lst))
		execArgsPiped(cmd_lst);
	if (ft_strncmp(cmd_lst->args[0], "exit", 4) == 0)
		return (EXIT);
	else if (ft_strncmp(cmd_lst->args[0], "export", 6) == 0)
		return (EXPORT);
	else if (ft_strncmp(cmd_lst->args[0], "cd", 2) == 0)
		return (CD);
	cmd_handler(env_lst, input);
	return (0);
}
