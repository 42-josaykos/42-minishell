/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 12:32:40 by jonny             #+#    #+#             */
/*   Updated: 2021/05/14 11:07:26 by jonny            ###   ########.fr       */
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

// static void	init_piped_cmd(enum e_type *types, t_cmd **piped_cmd, char *buffer)
// {
// 	t_cmd	*new_cmd;
// 	int		i;

// 	new_cmd = ft_calloc(1, sizeof(t_cmd));
// 	i = 0;
// 	while (types[i] != PIPE && types[i] != VOID)
// 	{
// 		new_cmd->type[i] = types[i];
// 		i++;
// 	}
// 	new_cmd->type[i] = VOID;
// 	new_cmd->args = split_whitespace(buffer);
// 	new_cmd->next = NULL;
// 	cmd_lst_add(piped_cmd, new_cmd);
// }

void		reset_buf(char *buffer, enum e_type *types)
{
	(void)buffer;
	// ft_bzero(buffer, BUF_SIZE);
	ft_bzero(types, BUF_SIZE);
}

void		concat_buf(char *buffer, char *str)
{
	ft_strcat(buffer, str);
	ft_strcat(buffer, " ");
}

void		parse_pipe(int i, int j, t_cmd *cmd_lst, t_cmd **piped_cmd)
{
	enum e_type	types[BUF_SIZE];
	(void)piped_cmd;
	t_cmd	*new_cmd;
	int		index;
	int		size;

	i = 0;
	j = 0;
	index = 0;
	reset_buf(NULL, types);
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

	// while (1)
	// {
		// if (cmd_lst->type[i] == PIPE || cmd_lst->type[i] == VOID)
		// {
			// types[j] = cmd_lst->type[i];
			// init_piped_cmd(types, piped_cmd, buffer);
			// if (cmd_lst->type[i] == VOID)
				// break ;
			// reset_buf(buffer, types);
			// j = 0;
		// }
		// else
		// {
			// types[j] = cmd_lst->type[i];
			// concat_buf(buffer, cmd_lst->args[i]);
			// j++;
		// }
		// i++;
	// }
}
