/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 11:32:39 by jonny             #+#    #+#             */
/*   Updated: 2021/05/27 12:37:21 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/msh.h"

int	is_exec_path(char *str)
{
	struct stat	filestat;

	if (file_exists(str))
	{
		stat(str, &filestat);
		if (S_ISDIR(filestat.st_mode))
			return (2);
		else if ((filestat.st_mode & S_IXUSR) != S_IXUSR)
			return (3);
		return (1);
	}
	return (0);
}

int	check_filepath(char *ptr, t_cmd *cmd_lst)
{
	char	filepath[BUF_SIZE];
	char	*tmp;
	int		len;

	len = 0;
	if (is_exec_path(*cmd_lst->args))
		return (is_exec_path(*cmd_lst->args));
	while (ptr)
	{
		tmp = ft_strsep(&ptr, ":");
		len = ft_strlen(tmp);
		ft_strlcpy(filepath, tmp, len + 1);
		if (filepath[len - 1] != '/')
			ft_strcat(filepath, "/");
		ft_strcat(filepath, *cmd_lst->args);
		if (file_exists(filepath))
		{
			if (*cmd_lst->args)
				free(*cmd_lst->args);
			*cmd_lst->args = ft_strdup(filepath);
			return (1);
		}
	}
	return (0);
}

void	error_num(int errnum, char *cmd, int exit_code)
{
	g_sig.exit_status = exit_code;
	ft_putstr_fd("msh: ", STDERR);
	ft_putstr_fd(cmd, STDERR);
	ft_putstr_fd(": ", STDERR);
	ft_putstr_fd(strerror(errnum), STDERR);
	ft_putstr_fd("\n", STDERR);
}

bool	filepath_exists(t_env *env_lst, t_cmd *cmd_lst)
{
	char	*ptr;
	char	copy[BUF_SIZE];
	int		ret;	

	ptr = NULL;
	while (env_lst)
	{
		if (!ft_strncmp(env_lst->key, "PATH", 5))
		{
			ft_strlcpy(copy, env_lst->value, ft_strlen(env_lst->value) + 1);
			ptr = copy;
			break ;
		}
		env_lst = env_lst->next;
	}
	ret = check_filepath(ptr, cmd_lst);
	if (ret == 1)
		return (true);
	else if (ret == 2)
		error_num(EISDIR, *cmd_lst->args, 126);
	else if (ret == 3)
		error_num(EACCES, *cmd_lst->args, 126);
	else
		error_cmd(*cmd_lst->args);
	return (false);
}
