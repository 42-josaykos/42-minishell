/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_piped_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 06:09:53 by jonny             #+#    #+#             */
/*   Updated: 2021/02/05 19:22:05 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../includes/msh.h"

static int	exec_process(char **envp, int in, int out, t_cmd *cmd_lst)
{
	pid_t	pid;

	if (!file_exists(*cmd_lst->args))
		cmd_lst->args[0] = cmd_lst->cmd;
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
		execve(*cmd_lst->args, cmd_lst->args, envp);
		exit(0);
	}
	wait(NULL);
	return (pid);
}

static void	fork_pipes (char **envp, int n, t_cmd *cmd_lst)
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
			pid = exec_process(envp, in, fd[1], cmd_lst);
			close(fd[1]);
			in = fd[0];
			n--;
			cmd_lst = cmd_lst->next;
		}
		exec_last_process(envp, in, cmd_lst);
		exit(0);
	}
	wait(NULL);
}

static void	piped_cmd_handler3(t_cmd *cmd_lst, char *filepath)
{
	t_cmd	*cmd_paths;
	char	uncat_path[MAXCHAR];
	t_cmd	*ptr;

	cmd_paths = cmd_lst;
	ptr = cmd_paths;
	while (ptr && ptr->args[0])
	{
		ft_strlcpy(uncat_path, filepath, ft_strlen(filepath) + 1);
		ft_strcat(filepath, ptr->args[0]);
		if (file_exists(filepath))
		{
			ft_strlcpy(ptr->cmd, filepath, ft_strlen(filepath) + 1);
			cmd_paths = cmd_paths->next;
		}
		ft_strlcpy(filepath, uncat_path, ft_strlen(filepath) + 1);
		ptr = ptr->next;
	}
}

static void	piped_cmd_handler2(char **envp, char *path, t_cmd *cmd_lst)
{
	char	filepath[MAXCHAR];
	char	*tmp;
	int		len;

	len = 0;
	while (path && cmd_lst)
	{
		tmp = ft_strsep(&path, ":");
		len = ft_strlen(tmp);
		ft_strlcpy(filepath, tmp, len + 1);
		if (filepath[len - 1] != '/')
			ft_strcat(filepath, "/");
		piped_cmd_handler3(cmd_lst, filepath);
	}
	len = cmd_lst_size(cmd_lst);
	fork_pipes(envp, len, cmd_lst);
}

void	piped_cmd_handler(t_state *status, t_env *env_lst, t_cmd *cmd_lst)
{
	char	*pathstr;
	char	copy[MAXCHAR];
	char	**envp;

	pathstr = NULL;
	envp = status->envp;
	while (env_lst)
	{
		if (!ft_strncmp(env_lst->key, "PATH", 4))
		{
			ft_strlcpy(copy, env_lst->value, ft_strlen(env_lst->value) + 1);
			pathstr = copy;
			break ;
		}
		env_lst = env_lst->next;
	}
	piped_cmd_handler2(envp, pathstr, cmd_lst);
}
