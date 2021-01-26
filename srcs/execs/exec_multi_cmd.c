/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multi_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 15:21:45 by jonny             #+#    #+#             */
/*   Updated: 2021/01/26 15:50:58 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/msh.h"

static void	exec_multi_cmd(char **envp, int n, t_cmd *cmd_lst)
{
	pid_t	pid;

	if (create_fork(&pid) < 0 )
		exit(-1);
	while (n > 0)
	{
		if (pid == 0)
		{
			if (!file_exists(*cmd_lst->args))
				cmd_lst->args[0] = cmd_lst->cmd;
			execve(*cmd_lst->args, cmd_lst->args, envp);
			exit(0);
		}
		n--;
		cmd_lst = cmd_lst->next;
		wait(NULL);
	}
}

static void	multi_cmd_handler3(t_cmd *cmd_lst, char *filepath)
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

static void	multi_cmd_handler2(char **envp, char *path, t_cmd *cmd_lst)
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
		multi_cmd_handler3(cmd_lst, filepath);
	}
	len = cmd_lst_size(cmd_lst);
	exec_multi_cmd(envp, len, cmd_lst);
}

void 	multi_cmd_handler(char **envp, t_env *env_lst, t_cmd *cmd_lst)
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
	multi_cmd_handler2(envp, pathstr, cmd_lst);
}
