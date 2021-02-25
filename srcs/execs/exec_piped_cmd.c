/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_piped_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 06:09:53 by jonny             #+#    #+#             */
/*   Updated: 2021/02/25 11:22:34 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../includes/msh.h"

static void	exec_last_process(t_state *status, int in, t_cmd *cmd_lst)
{
	int	ret;

	ret = is_builtin(cmd_lst->args[0]);
	if (ret != CD && ret != EXPORT)
	{
		if (in != STDIN_FILENO)
			dup2(in, STDIN_FILENO);
		execve(*cmd_lst->args, cmd_lst->args, status->envp);
	}
}

static int	exec_process(t_state *st, int in, int out, t_cmd *cmd_lst)
{
	pid_t	pid;

	pid = 0;
	if (create_fork(&pid) < 0 )
		exit(-1);
	if (pid == 0)
	{
		if (in != 0)
		{
			dup2(in, STDIN_FILENO);
			close(in);
		}
		if (out != 0)
		{
			dup2(out, STDOUT_FILENO);
			close(out);
		}
		execve(*cmd_lst->args, cmd_lst->args, st->envp);
		if (g_sig.sigint || g_sig.sigquit)
			exit(g_sig.exit_status);
		else
			exit(EXIT_SUCCESS);
	}
	waitpid(pid, &st->code, 0);
	return (pid);
}

static void	fork_pipes (t_state *st, int n, t_cmd *cmd_lst)
{
	int		in;
	int		fd[2];

	if (create_fork(&g_sig.pid) < 0 )
		exit(EXIT_FAILURE);
	if (g_sig.pid == 0)
	{
		in = STDIN_FILENO;
		while (n - 1 > 0)
		{
			pipe(fd);
			exec_process(st, in, fd[1], cmd_lst);
			close(fd[1]);
			in = fd[0];
			n--;
			cmd_lst = cmd_lst->next;
		}
		exec_last_process(st, in, cmd_lst);
		if (g_sig.sigint || g_sig.sigquit)
			exit(g_sig.exit_status);
		else
			exit(EXIT_SUCCESS);
	}
	waitpid(g_sig.pid, &st->code, 0);
}

void 	has_piped_cmd(t_state *status, t_env *env_lst, char **args)
{
	char	buffer[BUF_SIZE];
	t_cmd	*piped_cmd;
	t_cmd	*ptr;
	int		len;

	piped_cmd = NULL;
	len = 0;
	ft_bzero(buffer, BUF_SIZE);
	while (*args && ft_strlen(*args))
	{
		ft_strcat(buffer, *args);
		ft_strcat(buffer, " ");
		args++;
	}
	parse_pipe(buffer, &piped_cmd);
	len = cmd_lst_size(piped_cmd);
	ptr = piped_cmd;
	while (ptr && *ptr->args)
	{
		filepath_exists(env_lst, ptr);
		ptr = ptr->next;
	}
	fork_pipes(status, len, piped_cmd);
	clear_previous_cmd(piped_cmd, status);
	free(piped_cmd);
}
