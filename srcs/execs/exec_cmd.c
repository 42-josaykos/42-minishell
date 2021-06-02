/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 12:21:20 by jonny             #+#    #+#             */
/*   Updated: 2021/06/02 18:19:53 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/msh.h"

static void	exec_cmd(t_state *st, char **args)
{
	if (create_fork(&g_sig.pid) < 0)
		exit(EXIT_FAILURE);
	if (g_sig.pid == 0)
	{
		execve(*args, args, st->envp);
		if (g_sig.sigint || g_sig.sigquit)
			exit(g_sig.exit_status);
		else
			exit(EXIT_SUCCESS);
	}
	else
		waitpid(g_sig.pid, &st->code, 0);
	if (st->code > 255)
		g_sig.exit_status = WEXITSTATUS(st->code);
}

static void	reset_fds(t_state *st)
{
	reset_std(st);
	close_fds(st);
	init_fds(&st);
}

static void	default_exec(t_state *st, t_env **env_lst, t_cmd *cmd_lst,
																	char *cmd)
{
	enum e_builtin	ret;

	ret = is_builtin(*cmd_lst->args);
	if (!ft_strncmp(*cmd_lst->args, "..", 3))
		error_cmd(*cmd_lst->args);
	else if (!ft_strncmp(*cmd_lst->args, ".", 2))
		error_cases(EINVAL, cmd, *cmd_lst->args);
	else if (ret)
		exec_builtin(ret, st, env_lst, cmd_lst);
	else if (!ft_strlen(*cmd_lst->args))
		error_cmd(*cmd_lst->args);
	else if (*cmd_lst->args && filepath_exists(*env_lst, cmd_lst))
		exec_cmd(st, cmd_lst->args);
}

void	cmd_handler2(t_cmd *cmd_lst, t_state *st, t_env **env_lst)
{
	char	*cmd;

	cmd = *cmd_lst->args;
	default_exec(st, env_lst, cmd_lst, cmd);
}

void	cmd_handler(t_state *st, t_env **env_lst, t_cmd *cmd_lst)
{
	sig_init(*cmd_lst->args);
	while (cmd_lst && *cmd_lst->args && g_sig.sigint == 0)
	{
		if (check_pipe(cmd_lst))
		{
			has_piped_cmd(st, *env_lst, cmd_lst);
			g_sig.pipe = 0;
		}
		else
		{
			parse_redirection(st, cmd_lst);
			if (cmd_lst && *cmd_lst->args && g_sig.exit_status != 1)
				cmd_handler2(cmd_lst, st, env_lst);
			else if (cmd_lst && *cmd_lst->args
				&& !ft_strncmp(*cmd_lst->args, "exit", 5))
				cmd_handler2(cmd_lst, st, env_lst);
		}
		cmd_lst = cmd_lst->next;
		reset_fds(st);
		if (cmd_lst != NULL && g_sig.sigint == 0)
			sig_init(*cmd_lst->args);
	}
}
