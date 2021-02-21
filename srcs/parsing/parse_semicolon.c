/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_semicolon.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 11:56:34 by jonny             #+#    #+#             */
/*   Updated: 2021/02/21 21:26:18 by jonny            ###   ########.fr       */
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
	if (check_semicolon((*cmd_lst)->args))
	{
		clear_previous_cmd(*cmd_lst, NULL);
	}
}