/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_piped_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 06:09:53 by jonny             #+#    #+#             */
/*   Updated: 2021/01/21 16:10:35 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../includes/msh.h"
#include <stdio.h>
#include <unistd.h>

void	exec_piped_cmd(t_cmd *cmd_lst)
{
	char	**args[MAXLIST];
	int		fd[2];
	pid_t	p1;
	pid_t	p2;
	int		i;

	i = 0;
	while (cmd_lst)
	{
		if (!file_exists(*cmd_lst->args))
			cmd_lst->args[0] = cmd_lst->cmd;
		args[i] = cmd_lst->args;
		cmd_lst = cmd_lst->next;
		i++;
	}
	if (pipe(fd) == -1)
	{
		printf("pipe failed\n");
		return ;
	}
	p1 = fork();
	if (p1 < 0)
	{
		printf("fork failed\n");
		return ;
	}
	if (p1 == 0)
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		execve(*args[1], args[1], NULL);
		exit(0);
	}
	else
	{
		p2 = fork();
		if (p2 < 0)
		{
			printf("fork failed\n");
			return ;
		}
		if (p2 == 0)
		{
			close(fd[0]);
			dup2(fd[1], STDOUT_FILENO);
			close(fd[1]);
			execve(*args[0], args[0], NULL);
			exit(0);
		}
		else
		{
			wait(NULL);
		}
	}
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
	exec_piped_cmd(cmd_lst);
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
