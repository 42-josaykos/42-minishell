/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_piped_cmd2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 15:52:35 by jonny             #+#    #+#             */
/*   Updated: 2021/02/03 12:05:01 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/msh.h"

void	exec_last_process(char **envp, int in, t_cmd *cmd_lst)
{
	int	ret;

	ret = is_builtin(cmd_lst->args[0]);
	if (ret != CD && ret != EXPORT)
	{
		if (in != STDIN_FILENO) // read from previous pipe from stdin
			dup2(in, STDIN_FILENO); // output to original standard output
		if (!file_exists(*cmd_lst->args))
			cmd_lst->args[0] = cmd_lst->cmd;
		execve(*cmd_lst->args, cmd_lst->args, envp);
	}
}
