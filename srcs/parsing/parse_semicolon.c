/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_semicolon.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 11:56:34 by jonny             #+#    #+#             */
/*   Updated: 2021/02/22 15:45:00 by jonny            ###   ########.fr       */
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

int		tab_size(char **tab)
{
	int i = 0;
	while (tab[i])
		i++;
	return (i);
}

void	init_cmd_lst(t_cmd **cmd_lst, char **args)
{
	int i = 0;
	int j = 0;
	int k = 0;
	int len = 0;
	char *tmp[BUF_SIZE];
	t_cmd *new_cmd;
	(void)cmd_lst;
	(void)args;

	ft_bzero(tmp, BUF_SIZE);
	while (args[i])
	{
		if (args[i][0] == ';')
		{
			new_cmd = ft_calloc(1, sizeof(t_cmd));
			len = tab_size(tmp);
			new_cmd->args = ft_calloc(len + 1, sizeof(char*));
			k = 0;
			while (tmp[k])
			{
				new_cmd->args[k] = ft_strdup(tmp[k]);
				k++;
			}
			new_cmd->args[k] = NULL;
			ft_bzero(tmp, BUF_SIZE);
			new_cmd->next = NULL;
			cmd_lst_add(cmd_lst, new_cmd);
			j = 0;
			i++;
			continue ;
		}
		tmp[j] = args[i];
		j++;
		i++;
	}
	new_cmd = ft_calloc(1, sizeof(t_cmd));
	new_cmd->args = ft_calloc(tab_size(args) + 1, sizeof(char*));
	k = 0;
	while (tmp[k])
	{
		new_cmd->args[k] = ft_strdup(tmp[k]);
		k++;
	}
	new_cmd->args[k] = NULL;
	ft_bzero(tmp, BUF_SIZE);
	new_cmd->next = NULL;
	cmd_lst_add(cmd_lst, new_cmd);
}

int	parse_semicolon(t_cmd **cmd_lst)
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
		clear_previous_cmd(*cmd_lst, NULL);
		init_cmd_lst(cmd_lst, args);
		i = 0;
		while (args[i])
		{
			free(args[i]);
			i++;
		}
		return (1);
	}
	return (0);
}