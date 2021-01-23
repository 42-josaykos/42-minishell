/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 12:21:20 by jonny             #+#    #+#             */
/*   Updated: 2021/01/23 17:00:12 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/msh.h"

/*
** Create a child process and execute the command in it. Parent process waits
** the child process to finish. read_path() reads the PATH and put it in the
** filepath[MAXCHAR] buffer. We add the filename to the path with ft_strcat()
*/

static void	exec_cmd(char **args)
{
	pid_t	p1;

	p1 = 0;
	if (create_fork(&p1) < 0 )
		exit(-1);
	if (p1 == 0)
	{
		execve(*args, args, NULL);
		exit(0);
	}
	wait(NULL);
}

/*
** Split PATH and look in each filepath for the command.
** If found, execute the command. 
*/

static void	*cmd_handler2(char *ptr, char **args)
{
	char	filepath[MAXCHAR];
	char	*tmp;
	int		len;

	len = 0;
	while (ptr)
	{
		tmp = ft_strsep(&ptr, ":");
		len = ft_strlen(tmp);
		ft_strlcpy(filepath, tmp, len + 1);
		if (filepath[len - 1] != '/')
			ft_strcat(filepath, "/");
		ft_strcat(filepath, args[0]);
		if (file_exists(filepath))
		{
			args[0] = filepath;
			exec_cmd(args);
			return (tmp);
		}
	}
	return (ptr);
}

/*
** Iterate through the env list for PATH, then try each filepath.
*/

void	cmd_handler(t_env *env_lst, char **args)
{
	char	*ptr;
	char	copy[MAXCHAR];

	ptr = NULL;
	if (file_exists(args[0]))
	{
		exec_cmd(args);
		return ;
	}
	while (env_lst)
	{
		if (!ft_strncmp(env_lst->key, "PATH", 4))
		{
			ft_strlcpy(copy, env_lst->value, ft_strlen(env_lst->value) + 1);
			ptr = copy;
			break ;
		}
		env_lst = env_lst->next;
	}
	if (cmd_handler2(ptr, args) == NULL)
		printf("minishell: %s: not found...\n", args[0]);
}
