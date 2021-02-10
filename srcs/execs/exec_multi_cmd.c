/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multi_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 15:21:45 by jonny             #+#    #+#             */
/*   Updated: 2021/02/10 11:19:44 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/msh.h"

static int 	has_piped_cmd(t_state *status, t_env *env_lst, char **args)
{
	int		i;
	char	buffer[BUF_SIZE];
	t_cmd	*piped_cmd;

	i = 0;
	piped_cmd = NULL;
	ft_bzero(buffer, BUF_SIZE);
	piped_cmd = ft_calloc(1, sizeof(t_cmd));
	while (args[i])
	{
		ft_strcat(buffer, args[i]);
		ft_strcat(buffer, " ");
		i++;
	}
	if (check_pipe(buffer, piped_cmd))
	{
		piped_cmd_handler(status, env_lst, piped_cmd);
		free_cmd_lst(&piped_cmd);
		return (1);
	}
	free(piped_cmd);
	return (0);
}

static void	exec_multi_cmd(t_state *st, t_env *env_lst, int n, t_cmd *cmd_lst)
{
	pid_t	pid;

	pid = 0;
	while (n > 0)
	{
		pid = is_builtin(*cmd_lst->args);
		if (!file_exists(*cmd_lst->args))
			cmd_lst->args[0] = cmd_lst->cmd;
		if (pid)
			exec_builtin(pid, st, env_lst, cmd_lst);
		else if (!has_piped_cmd(st, env_lst, cmd_lst->args))
		{
			if (create_fork(&pid) < 0 )
				exit(-1);
			if (pid == 0)
			{
				execve(*cmd_lst->args, cmd_lst->args, st->envp);
				exit(st->code);
			}
		}
		cmd_lst = cmd_lst->next;
		n--;
		waitpid(pid, &st->code, 0);
	}
}

static void	multi_cmd_handler3(t_cmd *cmd_lst, char *filepath)
{
	t_cmd	*cmd_paths;
	char	uncat_path[BUF_SIZE];
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

void	multi_cmd_handler2(t_state *st, t_env *env_lst, char *s, t_cmd *cmd_lst)
{
	char	filepath[BUF_SIZE];
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
	exec_multi_cmd(st, env_lst, len, cmd_lst);
}

void 	multi_cmd_handler(t_state *status, t_env *env_lst, t_cmd *cmd_lst)
{
	char	*pathstr;
	char	copy[BUF_SIZE];

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
	multi_cmd_handler2(status, env_lst, pathstr, cmd_lst);
}
