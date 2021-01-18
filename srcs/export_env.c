/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 15:04:59 by jonny             #+#    #+#             */
/*   Updated: 2021/01/18 10:25:11 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static void	content_add(t_env *node, char *key, char *value)
{
	ft_strlcpy(node->key, key, ft_strlen(key) + 1);
	ft_strlcpy(node->value, value, ft_strlen(value) + 1);
}

/*
** Create a new env variable (key=value) and add it to the env list.
*/

void	*export_env(t_env **env_lst, char *key, char *value)
{
	t_env	*new_env;
	t_env	*tmp;

	tmp = *env_lst;
	if (!key)
		key = "export";
	if (!value)
		value = "";
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, key, ft_strlen(key) + 1))
		{
			content_add(tmp, key, value);
			return (tmp);
		}
		tmp = (tmp)->next;
	}
	new_env = malloc(sizeof(t_env));
	if (!new_env)
		return (NULL);
	new_env->next = NULL;
	content_add(new_env, key, value);
	env_lst_add(env_lst, new_env);
	return (new_env);
}
