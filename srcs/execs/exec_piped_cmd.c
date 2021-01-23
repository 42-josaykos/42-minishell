/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_piped_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 06:09:53 by jonny             #+#    #+#             */
/*   Updated: 2021/01/23 16:40:30 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../includes/msh.h"

int	exec_process(int in, int out, t_cmd *cmd_lst)
{
	pid_t	pid;

	if (!file_exists(*cmd_lst->args))
		cmd_lst->args[0] = cmd_lst->cmd;
	pid = fork();
	if (pid < 0 )
	{
		ft_printf("Cannot execute child process.\n");
		exit(-1);
	}
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
		execve(*cmd_lst->args, cmd_lst->args, NULL);
		exit(0);
	}
	wait(NULL);
	return (pid);
}

void	fork_pipes (int n, t_cmd *cmd_lst)
{
	int		in;
	int		fd[2];
	pid_t	pid;
	pid_t	last_process;

	last_process = fork();
	if (last_process < 0 )
	{
		ft_printf("Cannot execute child process.\n");
		exit(-1);
	}
	if (last_process == 0)
	{
		in = STDIN_FILENO; // get input from standard input;
		while (n - 1 > 0)
		{
			pipe(fd);
			pid = exec_process(in, fd[1], cmd_lst);
			close(fd[1]); // close write side of the pipe
			in = fd[0]; // input of next process is the read side of the pipe
			n--;
			cmd_lst = cmd_lst->next;
		}
		if (in != STDIN_FILENO) // read from previous pipe from stdin
			dup2(in, STDIN_FILENO); // output to original standard output
		if (!file_exists(*cmd_lst->args))
			cmd_lst->args[0] = cmd_lst->cmd;
		execve(*cmd_lst->args, cmd_lst->args, NULL);
		exit(0);
	}
	wait(NULL);
}

void	piped_cmd_handler2(char *path, t_cmd *cmd_lst)
{
	char	filepath[MAXCHAR];
	char	*tmp;
	int		len;
	t_cmd	*ptr;
	t_cmd	*cmd_paths;
	char	uncat_path[MAXCHAR];

	len = 0;
	cmd_paths = cmd_lst;
	while (path && cmd_lst)
	{
		tmp = ft_strsep(&path, ":");
		len = ft_strlen(tmp);
		ft_strlcpy(filepath, tmp, len + 1);
		if (filepath[len - 1] != '/')
			ft_strcat(filepath, "/");
		ptr = cmd_paths;
		ft_strlcpy(uncat_path, filepath, ft_strlen(filepath) + 1);
		while (ptr && ptr->args[0])
		{
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
	len = cmd_lst_size(cmd_lst);
	fork_pipes(len, cmd_lst);
}

void	piped_cmd_handler(t_env *env_lst, t_cmd *cmd_lst)
{
	char	*pathstr;
	char	copy[MAXCHAR];

	pathstr = NULL;
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
	piped_cmd_handler2(pathstr, cmd_lst);
}
