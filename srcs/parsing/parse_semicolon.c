/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_semicolon.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 11:56:34 by jonny             #+#    #+#             */
/*   Updated: 2021/02/21 13:39:26 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/msh.h"

bool check_semicolon(char **args)
{
	int i = 0;
	while (args[i])
	{
		if (args[i][0] == ';')
			return (true);
		i++;
	}
	return (false);
}

void	parse_semicolon(t_cmd **cmd_lst)
{
	int i = 0;
	char **tmp;
	char buffer[BUF_SIZE];
	ft_bzero(buffer, BUF_SIZE);
	if (check_semicolon((*cmd_lst)->args))
	{
		while ((*cmd_lst)->args[i])
		{
			ft_strcat(buffer, (*cmd_lst)->args[i]);
			ft_strcat(buffer, " ");
			i++;
		}
		tmp = split_whitespace(buffer);
		free_2darray((*cmd_lst)->args);
	}
}