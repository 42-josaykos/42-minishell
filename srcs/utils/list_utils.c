/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 16:53:09 by jonny             #+#    #+#             */
/*   Updated: 2021/02/15 11:20:59 by jonny            ###   ########.fr       */
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
	t_env	*ptr_lst;
	t_env	*temp;

	ptr_lst = *env_lst;
	while (ptr_lst)
	{
		temp = ptr_lst->next;
		free(ptr_lst);
		ptr_lst = temp;
	}
	*env_lst = NULL;
}

void	free_cmd_lst(t_cmd **cmd_lst)
{
	t_cmd	*ptr_lst;
	t_cmd	*temp;

	ptr_lst = *cmd_lst;
	while (*cmd_lst)
	{
		temp = ptr_lst->next;
		free(ptr_lst);
		ptr_lst = temp;
	}
	*cmd_lst = NULL;
}

/*
** clear multicommands, keeps one node in cmd_lst and cmd_lst->args = NULL
*/

void	clear_previous_cmd(t_cmd *cmd_lst, t_state *st)
{
	t_cmd	*ptr;
	t_cmd	*tmp;

	st->has_semicolon = false;
	st->has_pipe = false;
	free_2darray(cmd_lst->args);
	cmd_lst->args = NULL;
	ptr = cmd_lst->next;
	ft_bzero(cmd_lst->cmd, BUF_SIZE);
	cmd_lst->next = NULL;
	while (ptr)
	{
		tmp = ptr->next;
		free_2darray(ptr->args);
		free(ptr);
		ptr = tmp;
	}
}
