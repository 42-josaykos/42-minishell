/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 12:21:20 by jonny             #+#    #+#             */
/*   Updated: 2021/02/25 11:42:05 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/msh.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

static void	exec_cmd(t_state *st, char **args)
{
	if (create_fork(&g_sig.pid) < 0 )
		exit(EXIT_FAILURE);
	if (g_sig.pid == 0)
	{
		execve(*args, args, st->envp);
		if (g_sig.sigint || g_sig.sigquit)
			exit(g_sig.exit_status);
		else
			exit(EXIT_SUCCESS);
	}
	else
		waitpid(g_sig.pid, &st->code, 0);
	if (st->code > 255)
		g_sig.exit_status = WEXITSTATUS(st->code);
}

void	cmd_handler(t_state *st, t_env *env_lst, t_cmd *cmd_lst)
{
	char			*cmd;
	enum e_builtin	ret;
	t_cmd			*ptr;

	ptr = cmd_lst;
	sig_init();
	while (ptr && *ptr->args && g_sig.sigint == 0)
	{
		cmd = *ptr->args;
		if (st->has_pipe || check_pipe(ptr->args))
			has_piped_cmd(st, env_lst, ptr->args);
		else
		{
			ret = is_builtin(*ptr->args);
			if (ret)
				exec_builtin(ret, st, env_lst, ptr);
			else if (filepath_exists(env_lst, ptr))
				exec_cmd(st, ptr->args);
			else
				error_cmd(cmd);
		}
		ptr = ptr->next;
		if (ptr != NULL && g_sig.sigint == 0)
			sig_init();
	}
}
