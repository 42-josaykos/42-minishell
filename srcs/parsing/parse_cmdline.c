/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmdline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 10:22:20 by jonny             #+#    #+#             */
/*   Updated: 2021/02/05 14:54:40 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/msh.h"
#include <stdio.h>

void	parse_args(char *str, t_cmd *cmd_lst)
{
	int	i;

	i = 0;
	while (i < MAXLIST)
	{
		cmd_lst->args[i] = ft_strsep(&str, " \t");
		if (cmd_lst->args[i] == NULL)
			break ;
		if (strlen(cmd_lst->args[i]) == 0)
			i--;
		i++;
	}
}

/*
** Check the input.
** Returns 1 if "exit".
** Returns 2 if "export" command (debug test).
** Returns 3 if "cd".
** Check each path directories for the executable and execute it (cmd_handler).
*/

int	parse_cmdline(char **envp, t_env *env_lst, t_cmd *cmd_lst, char *input)
{
	int	ret;

	ret = 0;
	if (check_semicolon(input, cmd_lst))
	{
		multi_cmd_handler(envp, env_lst, cmd_lst);
		return (0);
	}
	else if (check_pipe(input, cmd_lst))
	{
		piped_cmd_handler(envp, env_lst, cmd_lst);
		return (0);
	}
	else
		parse_args(input, cmd_lst);
	ret = is_builtin(cmd_lst->args[0]);
	if (ret)
		exec_builtin(ret, envp, env_lst, cmd_lst);
	else
		cmd_handler(envp, env_lst, cmd_lst->args);
	return (ret);
}
