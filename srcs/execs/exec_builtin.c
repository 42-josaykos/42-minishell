/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 12:38:26 by jonny             #+#    #+#             */
/*   Updated: 2021/02/15 11:43:08 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/msh.h"

void	exec_builtin(int ret, t_state *status, t_env *env_lst, t_cmd *cmd_lst)
{
	if (ret == EXIT)
		exit_msh(status, env_lst, cmd_lst);
	else if (ret == EXPORT)
		assign_env(cmd_lst->args[1], &env_lst);
	else if (ret == CD)
		cd(cmd_lst->args[1], env_lst);
	else if (ret == PWD)
		print_cwd();
	else if (ret == ECHO)
		echo(cmd_lst->args, env_lst, 0);
	else if (ret == ENV)
	{
		print_env_lst(status->envp);
		status->code = 43;
	}
}

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (!ft_strncmp(cmd, "exit", 5))
		return (EXIT);
	else if (!ft_strncmp(cmd, "export", 7))
		return (EXPORT);
	else if (!ft_strncmp(cmd, "cd", 3))
		return (CD);
	else if (!ft_strncmp(cmd, "pwd", 4))
		return (PWD);
	else if (!ft_strncmp(cmd, "echo", 5))
		return (ECHO);
	else if (!ft_strncmp(cmd, "env", 4))
		return (ENV);
	return (0);
}
