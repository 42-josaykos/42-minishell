/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 12:32:40 by jonny             #+#    #+#             */
/*   Updated: 2021/01/20 16:30:29 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/msh.h"

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

int	check_pipe(char *input, t_cmd *cmd_lst)
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
		return (1);
	}
	return (0);
}
