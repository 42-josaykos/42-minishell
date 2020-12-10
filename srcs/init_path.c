/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <jonny@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 14:30:32 by jonny             #+#    #+#             */
/*   Updated: 2020/12/10 11:46:45 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

void	init_path(int fd)
{
	int ret = 1;
	char *line = NULL;
	char **strs = NULL;
	char **sub_strs = NULL;
	t_envp env;

	while ((ret = get_next_line(fd, &line)) > 0)
	{
		strs = ft_split(line, ' ');
		free(line);

		while (*strs)
		{ 
			if (ft_strncmp(*strs, "export", 6) == 0)
			{
				sub_strs = ft_split(*(strs + 1), '=');
				env.key = *(sub_strs);
				env.value = *(sub_strs + 1);
				ft_printf("env.key = %s\n", env.key);
				ft_printf("env.value = %s\n", env.value);
			}
			strs++;
		}
	}
}
