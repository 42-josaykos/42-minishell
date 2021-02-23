/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 12:21:20 by jonny             #+#    #+#             */
/*   Updated: 2021/02/23 15:37:45 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/msh.h"

static void	exec_cmd(t_state *st, char **args)
{
	pid_t	p1;

	p1 = 0;
	if (create_fork(&p1) < 0 )
		exit(-1);
	if (p1 == 0)
	{
		execve(*args, args, st->envp);
		exit(0);
	}
	waitpid(p1, &st->code, 0);
}

void	cmd_handler(t_state *st, t_env *env_lst, t_cmd *cmd_lst)
{
	char			*cmd;
	enum e_builtin	ret;
	t_cmd			*ptr;

	ptr = cmd_lst;
	while (ptr && *ptr->args)
	{
		cmd = *ptr->args;
		if (st->has_pipe || check_pipe(ptr->args))
			has_piped_cmd(st, env_lst, ptr->args);
		else
		{
			ret = is_builtin(*ptr->args);
			if (ret)
				exec_builtin(ret, st, env_lst, ptr);
			else if (filepath_exists(env_lst, ptr))
				exec_cmd(st, ptr->args);
			else
				error_cmd(cmd);
		}
		ptr = ptr->next;
	}
}
