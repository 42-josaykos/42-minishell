/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 12:21:20 by jonny             #+#    #+#             */
/*   Updated: 2021/02/12 16:03:32 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/msh.h"

static void	exec_cmd(char **envp, char **args)
{
	pid_t	p1;

	p1 = 0;
	if (create_fork(&p1) < 0 )
		exit(-1);
	if (p1 == 0)
	{
		execve(*args, args, envp);
		exit(0);
	}
	wait(NULL);
}

void	cmd_handler(t_state *st, t_env *env_lst, t_cmd *cmd_lst)
{
	char *cmd;

	while (cmd_lst && *cmd_lst->args)
	{
		cmd = cmd_lst->args[0];
		if (filepath_exists(env_lst, cmd_lst))
		{
			exec_cmd(st->envp, cmd_lst->args);
		}
		else
		{
			ft_putstr_fd("minishell: ", STDERR);
			ft_putstr_fd(cmd, STDERR);
			ft_putstr_fd(" : command not found\n", STDERR);	
		}
		cmd_lst = cmd_lst->next;
	}
}
