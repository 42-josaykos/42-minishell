/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 16:53:09 by jonny             #+#    #+#             */
/*   Updated: 2021/01/21 16:11:40 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/msh.h"

/*
** Add a new env variable (key=value) at the end of the env list.
** Should be call in export_env function below.
*/

void	env_lst_add(t_env **env_lst, t_env *new_env)
{
	t_env	*tmp;

	if (env_lst != NULL)
	{
		if (*env_lst == NULL)
			*env_lst = new_env;
		else
		{
			tmp = *env_lst;
			while (tmp->next != NULL)
				tmp = tmp->next;
			tmp->next = new_env;
		}
	}
}

void	env_lst_remove(t_env *env_lst, char *key)
{
	t_env	*previous_node;

	previous_node = env_lst;
	while (env_lst)
	{
		if (!ft_strncmp(env_lst->key, key, ft_strlen(key) + 1))
		{
			printf("env %s %s\n", env_lst->key, env_lst->value);
			previous_node->next = env_lst->next;
			free(env_lst);
			env_lst = previous_node;
		}
		previous_node = env_lst;
		env_lst = env_lst->next;
	}
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

void	free_cmd_lst(t_cmd **cmd_lst)
{
	t_cmd	*ptr;
	t_cmd	*tmp;

	ptr = *cmd_lst;
	while (ptr)
	{
		tmp = ptr->next;
		free(ptr);
		ptr = tmp;
	}
	*cmd_lst = NULL;
}

void	clear_previous_cmd(t_cmd *cmd_lst)
{
	t_cmd	*ptr;
	t_cmd	*tmp;

	ptr = cmd_lst->next;
	ft_bzero(cmd_lst->cmd, MAXCHAR);
	ft_bzero(cmd_lst->args, MAXCHAR);
	cmd_lst->next = NULL;
	while (ptr)
	{
		tmp = ptr->next;
		free(ptr);
		ptr = tmp;
	}
}
