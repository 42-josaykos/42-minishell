/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_semicolon.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 11:56:34 by jonny             #+#    #+#             */
/*   Updated: 2021/03/09 10:42:52 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/msh.h"

static void	create_new_cmd(t_cmd **cmd_lst, char **tmp)
{
	t_cmd	*new_cmd;
	int		k;

	k = 0;
	new_cmd = ft_calloc(1, sizeof(t_cmd));
	new_cmd->args = ft_calloc(tab_size(tmp) + 1, sizeof(char *));
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

static void	init_cmd_lst(t_cmd **cmd_lst, t_ast *token)
{
	int		j;
	char	*tmp[BUF_SIZE];

	j = 0;
	ft_bzero(tmp, BUF_SIZE);
	while (token)
	{
		if (token->type == SEMICOLON)
		{
			create_new_cmd(cmd_lst, tmp);
			j = 0;
			token = token->right;
			continue ;
		}
		tmp[j] = token->value;
		j++;
		token = token->right;
	}
	create_new_cmd(cmd_lst, tmp);
}

static bool	check_semicolon(t_ast *token)
{
	int	i;

	i = 0;
	while (token)
	{
		if (token->type == SEMICOLON)
			return (true);
		token = token->right;
	}
	return (false);
}

void	init_cmd_type(t_cmd **cmd_lst, t_ast *token)
{
	int		i;
	t_cmd	*ptr;

	ptr = *cmd_lst;
	while (ptr)
	{
		i = 0;
		while (token)
		{
			if (token->type == SEMICOLON)
			{
				token = token->right;
				break ;
			}
			ptr->type[i] = token->type;
			i++;
			token = token->right;
		}
		ptr = ptr->next;
	}
}

bool	parse_cmds(t_ast *token, t_cmd **cmd_lst)
{
	int	ret;

	ret = false;
	if (check_semicolon(token))
		ret = true;
	init_cmd_lst(cmd_lst, token);
	init_cmd_type(cmd_lst, token);
	return (ret);
}
