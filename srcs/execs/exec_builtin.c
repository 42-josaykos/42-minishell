/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 12:38:26 by jonny             #+#    #+#             */
/*   Updated: 2021/05/17 17:35:20 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/msh.h"

void	exec_builtin(int ret, t_state *status, t_env **env_lst, t_cmd *cmd_lst)
{
	if (ret == EXIT)
		exit_msh(status, *env_lst, cmd_lst);
	else if (ret == EXPORT)
		assign_env(cmd_lst->args[1], env_lst);
	else if (ret == CD)
	{
		if (cmd_lst->args[1] && cmd_lst->args[2])
		{
			g_sig.exit_status = 1;
			ft_putendl_fd("msh: cd: too many arguments", STDERR);
			return ;
		}
		cd(cmd_lst->args[1], *env_lst);
	}
	else if (ret == PWD)
		print_cwd();
	else if (ret == PRINT)
		builtin_echo(cmd_lst->args, *env_lst, 0);
	else if (ret == ENV)
		print_env_lst(*env_lst);
	else if (ret == UNSET)
		builtin_unset(cmd_lst->args, env_lst);
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
		return (PRINT);
	else if (!ft_strncmp(cmd, "env", 4))
		return (ENV);
	else if (!ft_strncmp(cmd, "unset", 4))
		return (UNSET);
	return (0);
}
