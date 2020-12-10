/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <jonny@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 14:30:32 by jonny             #+#    #+#             */
/*   Updated: 2020/12/10 15:09:58 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

/*
** Check for export variable in config file
*/

int		parse_envp(char *str)
{
	if (ft_strncmp(str, "export", 6) == 0)
		return (1);
	return (0);
}

void	assign_envp(char *str, t_env *env_lst)
{
	char	**sub_strs;
	int		i;

	i = 0;
	sub_strs = ft_split(str, '=');
	ft_strlcpy(env_lst->key, *(sub_strs), ft_strlen(*(sub_strs)) + 1);
	ft_strlcpy(env_lst->value, *(sub_strs + 1), ft_strlen(*(sub_strs + 1)) + 1);
	while (sub_strs[i] != NULL)
		free(sub_strs[i++]);
	free(sub_strs);
}

void	init_path(int fd, t_env *env_lst)
{
	int		ret;
	char	*line;
	char	**strs;
	char	**ptr;
	char	buf[MAXCHAR];

	ret = 1;
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
				assign_envp(*(strs + 1), env_lst);
			free(*strs);
			strs++;
		}
		free(ptr);
	}
	return ;
}

/*
** Delete et free le env list. Should be call in main function before return.
*/

void	free_env_lst(t_env **env_lst)
{
	t_env *ptr;
	t_env *tmp;

	ptr = *env_lst;
	while (ptr)
	{
		tmp = ptr->next;
		free(ptr);
		ptr = tmp;
	}
	*env_lst = NULL;
}
