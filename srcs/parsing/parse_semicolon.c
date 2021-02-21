/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_semicolon.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 11:56:34 by jonny             #+#    #+#             */
/*   Updated: 2021/02/21 21:55:51 by jonny            ###   ########.fr       */
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

void	init_cmd_lst(t_cmd **cmd_lst, char **args)
{
	(void)cmd_lst;
	(void)args;
}

void	parse_semicolon(t_cmd **cmd_lst)
{
	int i = 0;
	char *args[BUF_SIZE];
	ft_bzero(args, BUF_SIZE);
	if (check_semicolon((*cmd_lst)->args))
	{
		while ((*cmd_lst)->args[i])
		{
			args[i] = ft_strdup((*cmd_lst)->args[i]);
			i++;
		}
		init_cmd_lst(cmd_lst, args);
		clear_previous_cmd(*cmd_lst, NULL);
	}
	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
}