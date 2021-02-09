/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 12:21:20 by jonny             #+#    #+#             */
/*   Updated: 2021/02/09 16:14:03 by jonny            ###   ########.fr       */
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

void	cmd_handler(char **envp, t_env *env_lst, t_cmd *cmd_lst)
{
	char	*ptr;

	ptr = NULL;
	if (filepath_exists(env_lst, cmd_lst))
	{
		exec_cmd(envp, cmd_lst->args);
		return ;
	}
	printf("minishell: %s: not found...\n", cmd_lst->args[0]);
}
