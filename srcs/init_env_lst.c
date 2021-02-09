/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env_lst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 16:56:57 by jonny             #+#    #+#             */
/*   Updated: 2021/02/08 16:46:22 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/msh.h"

/*
** Create a new env (key=value) in the env list.
*/

void	assign_env(char *str, t_env **env_lst)
{
	int		i;
	char	*env[2];

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
		assign_env(envp[i], env_lst);
		i++;
	}
	if (*env_lst == NULL)
		export_env(env_lst, "export", "");
	return ;
}
