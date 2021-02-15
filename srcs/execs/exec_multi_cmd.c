/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multi_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 15:21:45 by jonny             #+#    #+#             */
/*   Updated: 2021/02/15 14:40:54 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/msh.h"

int 	has_piped_cmd(t_state *status, t_env *env_lst, char **args)
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

// static void	exec_multi_cmd(t_state *st, t_env *env_lst, int n, t_cmd *cmd_lst)
// {
// 	pid_t	pid;

// 	pid = 0;
// 	while (n > 0)
// 	{
// 		pid = is_builtin(*cmd_lst->args);
// 		if (!file_exists(*cmd_lst->args))
// 			cmd_lst->args[0] = cmd_lst->cmd;
// 		if (pid)
// 			exec_builtin(pid, st, env_lst, cmd_lst);
// 		else if (!has_piped_cmd(st, env_lst, cmd_lst->args))
// 		{
// 			if (create_fork(&pid) < 0 )
// 				exit(-1);
// 			if (pid == 0)
// 			{
// 				execve(*cmd_lst->args, cmd_lst->args, st->envp);
// 				exit(st->code);
// 			}
// 		}
// 		cmd_lst = cmd_lst->next;
// 		n--;
// 		waitpid(pid, &st->code, 0);
// 	}
// }
