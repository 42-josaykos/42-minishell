/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 09:58:12 by jonny             #+#    #+#             */
/*   Updated: 2021/03/18 10:33:19 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/msh.h"

static void	hist_add(t_hist **history, t_hist *new_node)
{
	t_hist	*tmp;

	tmp = *history;
	if (!(*history))
		*history = new_node;
	else
	{
		while ((*history)->next != NULL)
			*history = (*history)->next;
		(*history)->next = new_node;
		new_node->previous = *history;
		*history = tmp;
	}
}

void	hist_update(t_hist **history, char *buffer)
{
	t_hist	*new_node;

	new_node = ft_calloc(1, sizeof(t_ast));
	new_node->next = NULL;
	new_node->value = ft_strdup(buffer);
	hist_add(history, new_node);
}

void	free_hist(t_hist **history)
{
	t_hist	*ptr;
	t_hist	*tmp;

	ptr = *history;
	while (ptr)
	{
		tmp = ptr->next;
		if (ptr->value)
			free(ptr->value);
		free(ptr);
		ptr = tmp;
	}
	history = NULL;
}
