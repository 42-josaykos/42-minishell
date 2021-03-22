/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env_lst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 16:56:57 by jonny             #+#    #+#             */
/*   Updated: 2021/03/22 12:51:04 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/msh.h"

/*
** Create a new env (key=value) in the env list.
*/

void	assign_env(char *str, t_env **env_lst)
{
	int		i;
	char	*env[2];
	char *ptr = NULL;

	i = 0;
	env[0] = NULL;
	env[1] = NULL;
	if (!str)
	{
		print_export_variables(*env_lst);
		return ;
	}
	else if ((ptr = ft_strchr(str, '=')))
	{
		*ptr = '\0';
		ptr++;
		env[0] = ft_strdup(str);
		if (*ptr)
			env[1] = ft_strdup(ptr);
		else
		 	env[1] = ft_strdup("");
	}
	else
		env[0] = ft_strdup(str);
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
	return ;
}
