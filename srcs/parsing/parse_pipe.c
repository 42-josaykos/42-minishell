/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 12:32:40 by jonny             #+#    #+#             */
/*   Updated: 2021/05/14 11:19:52 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/msh.h"

bool		check_pipe(t_cmd *cmd_lst)
{
	int	i;

	i = 0;
	while (cmd_lst->type[i] != VOID)
	{
		if (cmd_lst->type[i] == PIPE)
			return (true);
		i++;
	}
	return (false);
}

void		parse_pipe(int i, int j, t_cmd *cmd_lst, t_cmd **piped_cmd)
{
	t_cmd	*new_cmd;
	int		index;
	int		size;

	i = 0;
	index = 0;
	while (1)
	{
		if (cmd_lst->type[i] == PIPE || cmd_lst->type[i] == VOID)
		{
			size = i - index + 1;
			new_cmd = ft_calloc(1, sizeof(t_cmd));
			new_cmd->next = NULL;
			new_cmd->args = ft_calloc(size, sizeof(char *));
			j = 0;
			while (index < i)
			{
				new_cmd->args[j] = ft_strdup(cmd_lst->args[index]);
				new_cmd->type[j] = cmd_lst->type[index];
				index++;
				j++;
			}
			index = i + 1;
			cmd_lst_add(piped_cmd, new_cmd);
		}
		if (cmd_lst->type[i] == VOID)
			break ;
		i++;
	}
}
