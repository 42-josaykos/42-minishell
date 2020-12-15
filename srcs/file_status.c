/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <jonny@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 11:31:49 by jonny             #+#    #+#             */
/*   Updated: 2020/12/15 15:25:00 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

/*
** Returns 0 if the file exists.
*/

int		file_exists(char *filename)
{
	struct stat buf;

	return (stat(filename, &buf));
}

/*
** Reads the PATH value. Check if the last char is '/' (we need it to concat
** the filepath with the filename later on)
*/

void	read_path(t_env *env_lst, char *filepath)
{
	char	path_value[MAXCHAR];
	int		len;

	ft_strlcpy(path_value, env_lst[0].value, ft_strlen(env_lst[0].value) + 1);
	len = ft_strlen(path_value);
	if (path_value[len - 1] != '/')
	{
		ft_strcat(path_value, "/");
		len++;
	}
	ft_strlcpy(filepath, path_value, len + 1);
}
