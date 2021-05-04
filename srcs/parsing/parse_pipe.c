/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 12:32:40 by jonny             #+#    #+#             */
/*   Updated: 2021/05/04 17:00:55 by jonny            ###   ########.fr       */
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

static void	init_piped_cmd(enum e_type *types, t_cmd **piped_cmd, char *buffer)
{
	t_cmd	*new_cmd;
	int		i;

	new_cmd = ft_calloc(1, sizeof(t_cmd));
	i = 0;
	while (types[i] != PIPE && types[i] != VOID)
	{
		new_cmd->type[i] = types[i];
		i++;
	}
	new_cmd->type[i] = VOID;
	new_cmd->args = split_whitespace(buffer);
	new_cmd->next = NULL;
	cmd_lst_add(piped_cmd, new_cmd);
}

void		reset_buf(char *buffer, enum e_type *types)
{
	ft_bzero(buffer, BUF_SIZE);
	ft_bzero(types, BUF_SIZE);
}

void		concat_buf(char *buffer, char *str)
{
	ft_strcat(buffer, str);
	ft_strcat(buffer, " ");
}

void		parse_pipe(int i, int j, t_cmd *cmd_lst, t_cmd **piped_cmd)
{
	char		buffer[BUF_SIZE];
	enum e_type	types[BUF_SIZE];

	i = 0;
	j = 0;
	reset_buf(buffer, types);
	while (1)
	{
		if (cmd_lst->type[i] == PIPE || cmd_lst->type[i] == VOID)
		{
			types[j] = cmd_lst->type[i];
			init_piped_cmd(types, piped_cmd, buffer);
			if (cmd_lst->type[i] == VOID)
				break ;
			reset_buf(buffer, types);
			j = 0;
		}
		else
		{
			types[j] = cmd_lst->type[i];
			concat_buf(buffer, cmd_lst->args[i]);
			j++;
		}
		i++;
	}
}
