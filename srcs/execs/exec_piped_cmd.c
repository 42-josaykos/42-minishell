/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_piped_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 06:09:53 by jonny             #+#    #+#             */
/*   Updated: 2021/02/21 23:20:34 by jonny            ###   ########.fr       */
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

static int	exec_process(t_state *status, int in, int out, t_cmd *cmd_lst)
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
		execve(*cmd_lst->args, cmd_lst->args, status->envp);
		exit(0);
	}
	waitpid(pid, &status->code, 0);
	return (pid);
}

static void	fork_pipes (t_state *status, int n, t_cmd *cmd_lst)
{
	int		in;
	int		fd[2];
	pid_t	pid;
	pid_t	last_process;

	last_process = 0;
	if (create_fork(&last_process) < 0 )
		exit(-1);
	if (last_process == 0)
	{
		in = STDIN_FILENO;
		while (n - 1 > 0)
		{
			pipe(fd);
			pid = exec_process(status, in, fd[1], cmd_lst);
			close(fd[1]);
			in = fd[0];
			n--;
			cmd_lst = cmd_lst->next;
		}
		exec_last_process(status, in, cmd_lst);
		exit(0);
	}
	waitpid(last_process, &status->code, 0);
}

void 	has_piped_cmd(t_state *status, t_env *env_lst, char **args)
{
	int		i;
	char	buffer[BUF_SIZE];
	t_cmd	*piped_cmd;
	t_cmd	*ptr;
	int		len;

	i = 0;
	piped_cmd = NULL;
	len = 0;
	ft_bzero(buffer, BUF_SIZE);
	while (args[i] && ft_strlen(args[i]))
	{
		ft_strcat(buffer, args[i]);
		ft_strcat(buffer, " ");
		i++;
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
