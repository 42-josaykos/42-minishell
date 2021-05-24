/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_piped_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 06:09:53 by jonny             #+#    #+#             */
/*   Updated: 2021/05/24 13:52:11 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/msh.h"

// void	exec_last_process(t_state *st, t_env *env_lst, int in,
// 																t_cmd *cmd_lst)
// {
// 	int	ret;

// 	parse_redirection(st, cmd_lst);
// 	ret = is_builtin(cmd_lst->args[0]);
// 	if (ret && ret != CD && ret != EXPORT)
// 		exec_builtin(ret, st, &env_lst, cmd_lst);
// 	else if (filepath_exists(env_lst, cmd_lst))
// 	{
// 		if (in != STDIN_FILENO && st->fdin == -1)
// 			dup2(in, STDIN_FILENO);
// 		execve(*cmd_lst->args, cmd_lst->args, st->envp);
// 	}
// }

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

// static int	create_process(t_state *st, t_env *env_lst, int in, t_cmd *cmd_lst)
// {
// 	pid_t	pid;

// 	pid = 0;
// 	if (create_fork(&pid) < 0)
// 		exit(-1);
// 	if (pid == 0)
// 	{
// 		if (in != 0)
// 		{
// 			dup2(in, STDIN_FILENO);
// 			close(in);
// 		}
// 		if (st->pipefd[1] != 0)
// 		{
// 			dup2(st->pipefd[1], STDOUT_FILENO);
// 			close(st->pipefd[1]);
// 		}
// 		exec_process(st, env_lst, cmd_lst);
// 		if (g_sig.sigint || g_sig.sigquit)
// 			exit(g_sig.exit_status);
// 		else
// 			exit(EXIT_SUCCESS);
// 	}
// 	waitpid(pid, &st->code, 0);
// 	return (pid);
// }

// void	fork_pipes(t_state *st, t_env *env_lst, int n, t_cmd *cmd_lst)
// {
// 	int		in;

// 	if (create_fork(&g_sig.pid) < 0)
// 		exit(EXIT_FAILURE);
// 	if (g_sig.pid == 0)
// 	{
// 		in = STDIN_FILENO;
// 		while (n - 1 > 0)
// 		{
// 			pipe(st->pipefd);
// 			create_process(st, env_lst, in, cmd_lst);
// 			close(st->pipefd[1]);
// 			in = st->pipefd[0];
// 			n--;
// 			cmd_lst = cmd_lst->next;
// 		}
// 		exec_last_process(st, env_lst, in, cmd_lst);
// 		exit(g_sig.exit_status);
// 	}
// 	waitpid(g_sig.pid, &st->code, 0);
// 	if (st->code > 255)
// 		g_sig.exit_status = WEXITSTATUS(st->code);
// }


void	fork_pipes2(t_state *st, t_env *env_lst, int n, t_cmd *cmd_lst)
{
	int pipefd[BUF_SIZE][2];
	pid_t childpid[BUF_SIZE];
	int i;

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
				dup2(pipefd[i - 1][0], STDIN); // get input from pipe
			}
			if (i != n - 1)
			{
				close(pipefd[i][0]); // close unused read end
				dup2(pipefd[i][1], STDOUT); // output go to pipe
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
