/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 11:32:39 by jonny             #+#    #+#             */
/*   Updated: 2021/02/10 11:19:16 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/msh.h"

bool	is_exec_path(char *str)
{
	if (*str == '/')
	{
		if (file_exists(str))
			return (true);
	}
	else if (str[0] == '.' && str[1] == '/')
	{
		if (file_exists(str))
			return (true);
	}
	return (false);
}

bool	check_filepath(char *ptr, t_cmd *cmd_lst)
{
	char	filepath[BUF_SIZE];
	char	*tmp;
	int		len;

	len = 0;
	if (is_exec_path(*cmd_lst->args))
		return (true);
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
			return (true);
		}
	}
	return (false);
}

bool	filepath_exists(t_env *env_lst, t_cmd *cmd_lst)
{
	char	*ptr;
	char	copy[BUF_SIZE];

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
	if (check_filepath(ptr, cmd_lst))
		return (true);
	return (false);
}
