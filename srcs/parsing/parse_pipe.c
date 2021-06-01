/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 12:32:40 by jonny             #+#    #+#             */
/*   Updated: 2021/06/01 09:56:56 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/msh.h"

bool	check_pipe(t_cmd *cmd_lst)
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

void	create_cmd_args(t_cmd *new_cmd, t_cmd *cmd_lst, int i, int index)
{
	int	j;

	j = 0;
	while (index < i)
	{
		new_cmd->args[j] = ft_strdup(cmd_lst->args[index]);
		new_cmd->type[j] = cmd_lst->type[index];
		index++;
		j++;
	}
}

void	parse_pipe(t_cmd *cmd_lst, t_cmd **piped_cmd)
{
	t_cmd	*new_cmd;
	int		index;
	int		size;
	int		i;

	i = 0;
	index = 0;
	new_cmd = NULL;
	while (1)
	{
		if (cmd_lst->type[i] == PIPE || cmd_lst->type[i] == VOID)
		{
			size = i - index + 1;
			new_cmd = ft_calloc(1, sizeof(t_cmd));
			new_cmd->next = NULL;
			new_cmd->args = ft_calloc(size, sizeof(char *));
			create_cmd_args(new_cmd, cmd_lst, i, index);
			index = i + 1;
			cmd_lst_add(piped_cmd, new_cmd);
		}
		if (cmd_lst->type[i] == VOID)
			break ;
		i++;
	}
}

void	has_piped_cmd(t_state *status, t_env *env_lst, t_cmd *cmd_lst)
{
	t_cmd	*piped_cmd;
	int		len;
	int		i;
	int		j;

	piped_cmd = NULL;
	len = 0;
	i = 0;
	j = 0;
	g_sig.pipe = 1;
	parse_pipe(cmd_lst, &piped_cmd);
	len = cmd_lst_size(piped_cmd);
	fork_pipes2(status, env_lst, len, piped_cmd);
	clear_previous_cmd(piped_cmd, status);
	free(piped_cmd);
}
