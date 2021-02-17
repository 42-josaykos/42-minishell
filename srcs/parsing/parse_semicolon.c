/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_semicolon.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 13:04:23 by jonny             #+#    #+#             */
/*   Updated: 2021/02/17 11:10:27 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/msh.h"

bool	parse_semicolon(char *str, char **args)
{
	int	i;

	i = 0;
	while (i < BUF_SIZE)
	{
		args[i] = ft_strsep(&str, ";");
		if (args[i] == NULL)
			break ;
		if (strlen(args[i]) == 0)
			i--;
		i++;
	}
	if (args[1] == NULL)
		return (false);
	return (true);
}

int	check_semicolon(char *input, t_cmd *cmd_lst)
{
	char	*tmp[BUF_SIZE];
	t_cmd	*new_cmd;
	int		i;

	new_cmd = NULL;
	if (parse_semicolon(input, tmp) == true)
	{
		i = 0;
		while (tmp[i])
		{
			new_cmd = ft_calloc(1, sizeof(t_cmd));
			new_cmd->next = NULL;
			cmd_lst_add(&cmd_lst, new_cmd);
			cmd_lst = cmd_lst->next;
			i++;
		}
		return (1);
	}
	return (0);
}
