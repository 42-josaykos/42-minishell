/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_piped_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 06:09:53 by jonny             #+#    #+#             */
/*   Updated: 2021/05/30 15:04:15 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/msh.h"
#include <sys/wait.h>

static void	close_dup_pipes(int i, int n, int pipefd[BUF_SIZE][2])
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
}

static void	exec_piped_cmd(t_state *st, t_env *env_lst, t_cmd *cmd_lst)
{
	int		ret;

	parse_redirection(st, cmd_lst);
	ret = is_builtin(cmd_lst->args[0]);
	if (ret == EXIT)
		return ;
	if (ret)
		exec_builtin(ret, st, &env_lst, cmd_lst);
	else if (!ft_strlen(*cmd_lst->args))
		error_cmd(*cmd_lst->args);
	else if (filepath_exists(env_lst, cmd_lst))
		execve(*cmd_lst->args, cmd_lst->args, st->envp);
}

static void	close_pipes(int i, int pipefd[BUF_SIZE][2])
{
	if (i != 0)
	{
		close(pipefd[i - 1][0]);
		close(pipefd[i - 1][1]);
	}
}

static void	wait_forks(int n, t_state *st)
{
	while (n > 0)
	{
		waitpid(-1, &st->code, 0);
		if (st->code > 255)
			g_sig.exit_status = WEXITSTATUS(st->code);
		n--;
	}
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
			close_dup_pipes(i, n, pipefd);
			exec_piped_cmd(st, env_lst, cmd_lst);
			if (g_sig.sigint || g_sig.sigquit)
				exit(g_sig.exit_status);
			exit (g_sig.exit_status);
		}
		close_pipes(i, pipefd);
		cmd_lst = cmd_lst->next;
		i++;
	}
	wait_forks(n, st);
}
