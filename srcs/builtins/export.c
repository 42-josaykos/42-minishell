/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 15:04:59 by jonny             #+#    #+#             */
/*   Updated: 2021/03/22 13:56:14 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/msh.h"

static void	content_add(t_env *node, char *key, char *value)
{
	if (key)
		node->key = key;
	if (value)
		node->value = value;
}

/*
** Create a new env variable (key=value) and add it to the env list.
*/

void	*export_env(t_env **env_lst, char *key, char *value)
{
	t_env	*new_env;
	t_env	*tmp;

	tmp = *env_lst;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, key, ft_strlen(key) + 1))
		{
			free(tmp->key);
			free(tmp->value);
			content_add(tmp, key, value);
			return (tmp);
		}
		tmp = (tmp)->next;
	}
	new_env = ft_calloc(1, sizeof(t_env));
	if (!new_env)
		return (NULL);
	new_env->next = NULL;
	content_add(new_env, key, value);
	env_lst_add(env_lst, new_env);
	return (new_env);
}

void	print_export_variables(t_env *env_lst)
{
	char	env[BUF_SIZE];

	ft_bzero(env, BUF_SIZE);
	while (env_lst)
	{
		ft_strlcat(env, "export ", BUF_SIZE);
		ft_strlcat(env, env_lst->key, BUF_SIZE);
		if (env_lst->value)
		{
			ft_strlcat(env, "=", BUF_SIZE);
			ft_strlcat(env, "\"", BUF_SIZE);
			ft_strlcat(env, env_lst->value, BUF_SIZE);
			ft_strlcat(env, "\"", BUF_SIZE);
		}
		ft_putendl_fd(env, STDOUT);
		ft_bzero(env, BUF_SIZE);
		env_lst = env_lst->next;
	}
}
