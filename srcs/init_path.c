/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 14:30:32 by jonny             #+#    #+#             */
/*   Updated: 2021/01/17 13:35:42 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

/*
** Check for "export" command in the line. Returns 1 if "export" is present.
*/

int	parse_envp(char *str)
{
	if (ft_strncmp(str, "export", 6) == 0)
		return (1);
	return (0);
}

/*
** Create a new env (key=value) in the env list.
*/

void	assign_envp(char *str, t_env **env_lst)
{
	int		i;
	char	*env[2];

	(void)env_lst;
	i = 0;
	while (i < 2)
	{
		env[i] = ft_strsep(&str, "=");
		if (env[i] == NULL)
			break ;
		if (strlen(env[i]) == 0)
			i--;
		i++;
	}
	export_env(env_lst, env[0], env[1]);
}

void	init_env(t_env **env_lst, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		assign_envp(envp[i], env_lst);
		i++;
	}
	return ;
}

/*
** Delete and free the env list. Should be call in main function before return.
*/

void	free_env_lst(t_env **env_lst)
{
	t_env	*ptr;
	t_env	*tmp;

	ptr = *env_lst;
	while (ptr)
	{
		tmp = ptr->next;
		free(ptr);
		ptr = tmp;
	}
	*env_lst = NULL;
}
