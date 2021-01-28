/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multi_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 15:21:45 by jonny             #+#    #+#             */
/*   Updated: 2021/01/28 16:11:28 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/msh.h"
#include <sys/wait.h>

static void	exec_multi_cmd(char **envp, t_env *env_lst, int n, t_cmd *cmd_lst)
{
	pid_t	pid;
	int		status;

	pid = 0;
	while (n > 0)
	{
		pid = is_builtin(*cmd_lst->args);
		if (!file_exists(*cmd_lst->args))
			cmd_lst->args[0] = cmd_lst->cmd;
		if (pid)
			exec_builtin(pid, env_lst, cmd_lst);
		else
		{
			if (create_fork(&pid) < 0 )
				exit(-1);
			if (pid == 0)
			{
				execve(*cmd_lst->args, cmd_lst->args, envp);
				exit(status);
			}
		}
		cmd_lst = cmd_lst->next;
		n--;
		waitpid(pid, &status, WCONTINUED);
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

void	multi_cmd_handler2(char **envp, t_env *env_lst, char *s, t_cmd *cmd_lst)
{
	char	filepath[MAXCHAR];
	char	*tmp;
	int		len;

	len = 0;
	while (s && cmd_lst)
	{
		tmp = ft_strsep(&s, ":");
		len = ft_strlen(tmp);
		ft_strlcpy(filepath, tmp, len + 1);
		if (filepath[len - 1] != '/')
			ft_strcat(filepath, "/");
		multi_cmd_handler3(cmd_lst, filepath);
	}
	len = cmd_lst_size(cmd_lst);
	exec_multi_cmd(envp, env_lst, len, cmd_lst);
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
	multi_cmd_handler2(envp, env_lst, pathstr, cmd_lst);
}
