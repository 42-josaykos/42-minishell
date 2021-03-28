/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_semicolon.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 11:56:34 by jonny             #+#    #+#             */
/*   Updated: 2021/03/28 12:34:34 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/msh.h"

void	token_lst_remove(t_ast **token)
{
	t_ast	*next_node;

	if (token)
	{
		next_node = (*token)->right;
		if (next_node)
			next_node->left = NULL;
		free((*token)->value);
		free(*token);
		*token = next_node;
	}
}

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
	// ft_bzero(tmp, BUF_SIZE);
	new_cmd->next = NULL;
	*cmd_lst = new_cmd;
	// cmd_lst_add(cmd_lst, new_cmd);
}

static void	init_cmd_lst(t_cmd **cmd_lst, t_ast **token)
{
	int		j;
	int i;
	char	*tmp[BUF_SIZE];

	j = 0;
	ft_bzero(tmp, BUF_SIZE);
	while (*token && (*token)->type != SEMICOLON)
	{
		tmp[j] = ft_strdup((*token)->value);
		j++;
		token_lst_remove(token);
		// token = (token)->right;
	}
	create_new_cmd(cmd_lst, tmp);
	i = 0;
	while (tmp[i])
	{
		free(tmp[i]);
		tmp[i] = NULL;
		i++;
	}
	j = 0;
	if (*token)
		token_lst_remove(token);
		// (token) = (token)->right;
}

// static bool	check_semicolon(t_ast *token)
// {
// 	int	i;

// 	i = 0;
// 	while (token)
// 	{
// 		if (token->type == SEMICOLON)
// 			return (true);
// 		token = token->right;
// 	}
// 	return (false);
// }

void	init_cmd_type(t_cmd **cmd_lst, t_ast **token)
{
	int		i;
	t_cmd	*ptr;

	ptr = *cmd_lst;
	while (ptr)
	{
		i = 0;
		while (token)
		{
			if (*token && (*token)->type == SEMICOLON)
			{
				*token = (*token)->right;
				break ;
			}
			ptr->type[i] = (*token)->type;
			i++;
			*token = (*token)->right;
		}
		ptr = ptr->next;
	}
}

void	parse_cmds(t_ast **token, t_cmd **cmd_lst)
{
	int	ret;

	ret = false;
	init_cmd_lst(cmd_lst, token);
}
