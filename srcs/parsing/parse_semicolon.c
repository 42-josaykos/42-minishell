/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_semicolon.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 11:56:34 by jonny             #+#    #+#             */
/*   Updated: 2021/02/21 12:37:47 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/msh.h"

void	parse_semicolon(char **args, t_cmd **cmd_lst)
{
	int i = 0;
	char tmp[BUF_SIZE];
	(void)cmd_lst;

	ft_bzero(tmp, BUF_SIZE);
	while (args[i])
	{
		ft_strcat(tmp, args[i]);
		ft_strcat(tmp, " ");
		i++;
	}
}