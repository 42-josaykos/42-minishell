/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 13:28:04 by jonny             #+#    #+#             */
/*   Updated: 2021/02/25 10:33:50 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/msh.h"

char	**free_2darray(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
	{
		free((void *)tab[i]);
		tab[i] = NULL;
		i++;
	}
	free(tab);
	return (NULL);
}

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

/*
** clear multicommands, keeps one node in cmd_lst and cmd_lst->args = NULL
*/

void	clear_previous_cmd(t_cmd *cmd_lst, t_state *st)
{
	t_cmd	*ptr;
	t_cmd	*tmp;

	if (st)
	{
		st->has_semicolon = false;
		st->has_pipe = false;
	}
	free_2darray(cmd_lst->args);
	cmd_lst->args = NULL;
	ptr = cmd_lst->next;
	cmd_lst->next = NULL;
	while (ptr)
	{
		tmp = ptr->next;
		free_2darray(ptr->args);
		free(ptr);
		ptr = tmp;
	}
}
