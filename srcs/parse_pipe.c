/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <jonny@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 12:32:40 by jonny             #+#    #+#             */
/*   Updated: 2021/01/15 16:06:45 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

bool	parse_pipe(char *str, char **piped)
{
	int	i;

	i = 0;
	while (i < 100)
	{
		piped[i] = ft_strsep(&str, "|");
		if (piped[i] == NULL)
			break ;
		i++;
	}
	if (piped[1] == NULL)
		return (false);
	return (true);
}

static void	cmd_lst_add(t_cmd **cmd_lst, t_cmd *new_cmd)
{
	t_cmd	*tmp;

	if (cmd_lst != NULL)
	{
		if (*cmd_lst == NULL)
			*cmd_lst = new_cmd;
		else
		{
			tmp = *cmd_lst;
			while (tmp->next != NULL)
				tmp = tmp->next;
			tmp->next = new_cmd;
		}
	}
}

void	check_pipe(char *input, t_cmd *cmd_lst)
{
	char	*tmp[100];
	t_cmd	*new_cmd;
	int		i;

	new_cmd = NULL;
	if (parse_pipe(input, tmp) == true)
	{
		i = 0;
		while (tmp[i])
		{
			parse_args(tmp[i], cmd_lst->args);
			new_cmd = malloc(sizeof(t_cmd));
			new_cmd->next = NULL;
			cmd_lst_add(&cmd_lst, new_cmd);
			cmd_lst = cmd_lst->next;
			i++;
		}
	}
	else
		parse_args(input, cmd_lst->args);
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
