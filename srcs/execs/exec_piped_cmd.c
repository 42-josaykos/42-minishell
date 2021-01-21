/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_piped_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 06:09:53 by jonny             #+#    #+#             */
/*   Updated: 2021/01/21 08:04:45 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../includes/msh.h"
#include <stdio.h>
#include <unistd.h>

void exec_piped_cmd(t_cmd *cmd_lst)
{
	int fd[2];
	pid_t p1, p2;

	int i = 0;
	char **args[MAXLIST];

	while (cmd_lst)
	{
		args[i] = cmd_lst->args;
		cmd_lst = cmd_lst->next;
		i++;
	}
	if (pipe(fd) == -1)
	{
		printf("pipe failed\n");
		return ;
	}
	p1= fork();
	if (p1 < 0)
	{
		printf("fork failed\n");
		return ;
	}
	if (p1 == 0)
	{
		/* child process */
		ft_printf("In child process 1\n");
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		execve(*args[0], args[0], NULL);
		exit(0);
	}
	else
	{
		/* parent process*/
		ft_printf("In child process 2\n");
		p2 = fork();
		if (p2 < 0)
		{
			printf("fork failed\n");
			return ;
		}
		if (p2 == 0)
		{
			close(fd[1]);
			dup2(fd[0], STDIN_FILENO);
			close(fd[0]);
			execve(*args[1], args[1], NULL);
			exit(0);
		}
		else
		{
			wait(NULL);
		}
	}
}