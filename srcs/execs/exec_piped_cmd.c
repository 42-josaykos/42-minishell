/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_piped_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 06:09:53 by jonny             #+#    #+#             */
/*   Updated: 2021/05/24 15:40:46 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/msh.h"

static void	exec_process(t_state *st, t_env *env_lst, t_cmd *cmd_lst)
{
	int		ret;

	parse_redirection(st, cmd_lst);
	ret = is_builtin(cmd_lst->args[0]);
	if (ret)
		exec_builtin(ret, st, &env_lst, cmd_lst);
	else if (filepath_exists(env_lst, cmd_lst))
		execve(*cmd_lst->args, cmd_lst->args, st->envp);
}

void	fork_pipes2(t_state *st, t_env *env_lst, int n, t_cmd *cmd_lst)
{
	int		pipefd[BUF_SIZE][2];
	pid_t	childpid[BUF_SIZE];
	int		i;

	i = 0;
	while (i < n - 1)
		pipe(pipefd[i++]);
	i = 0;
	while (i < n)
	{
		childpid[i] = fork();
		if (childpid[i] == 0)
		{
			if (i != 0)
			{
				close(pipefd[i - 1][1]);
				dup2(pipefd[i - 1][0], STDIN);
			}
			if (i != n - 1)
			{
				close(pipefd[i][0]);
				dup2(pipefd[i][1], STDOUT);
			}
			exec_process(st, env_lst, cmd_lst);
			if (g_sig.sigint || g_sig.sigquit)
				exit(g_sig.exit_status);
			exit (0);
		}
		if (i != 0)
		{
			close(pipefd[i - 1][0]);
			close(pipefd[i - 1][1]);
		}
		cmd_lst = cmd_lst->next;
		i++;
	}
	while (n > 0)
	{
		waitpid(-1, &st->code, 0);
		if (st->code > 255)
			g_sig.exit_status = WEXITSTATUS(st->code);
		n--;
	}
}

void	has_piped_cmd(t_state *status, t_env *env_lst, t_cmd *cmd_lst)
{
	t_cmd	*piped_cmd;
	int		len;
	int		i;
	int		j;

	piped_cmd = NULL;
	len = 0;
	i = 0;
	j = 0;
	parse_pipe(cmd_lst, &piped_cmd);
	len = cmd_lst_size(piped_cmd);
	fork_pipes2(status, env_lst, len, piped_cmd);
	clear_previous_cmd(piped_cmd, status);
	free(piped_cmd);
}
