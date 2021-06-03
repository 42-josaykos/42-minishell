/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_semicolon.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 11:56:34 by jonny             #+#    #+#             */
/*   Updated: 2021/06/03 11:18:15 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/msh.h"

void	token_lst_remove(t_ast **token)
{
	t_ast	*next_node;

	if (*token)
	{
		next_node = (*token)->right;
		if (next_node)
			next_node->left = NULL;
		free((*token)->value);
		free(*token);
		*token = next_node;
	}
}

static void	create_new_cmd(t_cmd **cmd_lst, char **tmp,
	enum e_type *type)
{
	t_cmd	*new_cmd;
	int		k;

	new_cmd = ft_calloc(1, sizeof(t_cmd));
	new_cmd->args = ft_calloc(tab_size(tmp) + 1, sizeof(char *));
	k = 0;
	while (tmp[k] && type[k])
	{
		new_cmd->args[k] = ft_strdup(tmp[k]);
		new_cmd->type[k] = type[k];
		k++;
	}
	new_cmd->args[k] = NULL;
	new_cmd->next = NULL;
	*cmd_lst = new_cmd;
}

void	parse_cmds(t_ast **token, t_cmd **cmd_lst)
{
	int			j;
	int			i;
	char		*tmp[BUF_SIZE];
	enum e_type	type[BUF_SIZE];

	j = 0;
	ft_bzero(tmp, BUF_SIZE);
	ft_bzero(type, BUF_SIZE);
	while (*token && (*token)->type != SEMICOLON)
	{
		tmp[j] = ft_strdup((*token)->value);
		type[j] = (*token)->type;
		j++;
		token_lst_remove(token);
	}
	create_new_cmd(cmd_lst, tmp, type);
	i = 0;
	while (i < BUF_SIZE && tmp[i])
	{
		tmp[i] = NULL;
		i++;
	}
	if (*token)
		token_lst_remove(token);
}
