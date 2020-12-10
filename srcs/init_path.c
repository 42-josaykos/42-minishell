/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <jonny@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 14:30:32 by jonny             #+#    #+#             */
/*   Updated: 2020/12/10 13:30:42 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

/*
** Check for export variable in config file
*/

int parse_envp(char *str)
{
	if (ft_strncmp(str, "export", 6) == 0)
		return (1);
	return (0);
}

void assign_envp(char *str)
{
	char **sub_strs = NULL;
	int i;
	t_envp env;

	i = 0;
	sub_strs = ft_split(str, '=');
	ft_strlcpy(env.key, *(sub_strs), ft_strlen(*(sub_strs)) + 1);
	ft_strlcpy(env.value, *(sub_strs + 1), ft_strlen(*(sub_strs + 1)) + 1);
	ft_printf("env.key = %s\n", env.key);
	ft_printf("env.value = %s\n", env.value);
	while (sub_strs[i] != NULL)
		free(sub_strs[i++]);
	free(sub_strs);
}

void	init_path(int fd)
{
	int ret = 1;
	char *line = NULL;
	char **strs = NULL;
	char buf[100];
	char **ptr;

	 while (ret > 0)
	 {
	 	ret = get_next_line(fd, &line);
		ft_strlcpy(buf, line, MAXCHAR);
		free(line);
		strs = ft_split(buf, ' ');
		ptr = strs;
	 	while (*strs)
		{ 
			if (parse_envp(*strs))
				assign_envp(*(strs + 1));
			free(*strs);
			strs++;
	 	}
		free(ptr);
	 }
	return ;
}
