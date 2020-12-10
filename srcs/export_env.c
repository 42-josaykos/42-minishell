/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 15:04:59 by jonny             #+#    #+#             */
/*   Updated: 2020/12/10 15:31:26 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

/*
** Add a new env variable (key=value) at the end of the env list.
** Should be call in export_env function below.
*/

static void	env_lst_add(t_env **env_lst, t_env *new_env)
{
	t_env *tmp;

	tmp = *env_lst;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new_env;
}

/*
** Create a new env variable (key=value) and add it to the env list.
*/

void		export_env(t_env **env_lst, char *key, char *value)
{
	t_env *new_env;

	new_env = malloc(sizeof(t_env));
	ft_strlcpy(new_env->key, key, ft_strlen(key) + 1);
	ft_strlcpy(new_env->value, value, ft_strlen(value) + 1);
	new_env->next = NULL;
	env_lst_add(env_lst, new_env);
}
