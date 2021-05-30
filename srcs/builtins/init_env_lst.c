/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env_lst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 16:56:57 by jonny             #+#    #+#             */
/*   Updated: 2021/05/30 16:49:29 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/msh.h"

/*
** Create a new env (key=value) in the env list.
*/

char	*set_value(char *ptr)
{
	int		len;
	char	*value;

	len = 0;
	value = NULL;
	(ptr)++;
	if (*ptr == '\"' || *ptr == '\'')
		ptr++;
	len = ft_strlen(ptr);
	if (*ptr)
		value = ft_strdup(ptr);
	else
		value = ft_strdup("");
	return (value);
}

char	*set_var(char *ptr)
{
	char	*var;
	int		i;

	i = 0;
	while (ptr[i])
	{
		if (ptr[i] == '=')
		{
			ptr[i] = '\0';
			break ;
		}
		i++;
	}
	var = ft_strdup(ptr);
	return (var);
}

void	assign_env(char *str, enum e_type type, t_env **env_lst)
{
	char	*env[2];
	char	*ptr;

	if (str[0] == '=' || (str[0] == '\0' && type == ARG))
	{
		ft_putendl_fd("msh: not a valid identifier", STDERR);
		g_sig.exit_status = 1;
		return ;
	}
	env[0] = NULL;
	env[1] = NULL;
	ptr = NULL;
	ptr = ft_strchr(str, '=');
	if (ptr)
	{
		env[0] = set_var(str);
		env[1] = set_value(ptr);
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
		assign_env(envp[i], ARG, env_lst);
		i++;
	}
	return ;
}
