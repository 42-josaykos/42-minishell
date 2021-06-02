/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 11:07:31 by jonny             #+#    #+#             */
/*   Updated: 2021/06/02 10:47:35 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/msh.h"

static bool	spc_tkn(t_ast *tkn)
{
	if (tkn->type == SEMICOLON || tkn->type == PIPE
		|| tkn->type == REDIR || tkn->type == APPEND
		|| tkn->type == INPUT)
		return (true);
	return (false);
}

void	interpreter2(t_ast **tkn, t_ast **new_tkn, t_env *env_lst,
																char *buf)
{
	t_ast	*new_node;

	if (spc_tkn(*tkn))
	{
		new_node = create_node(ft_strdup((*tkn)->value), (*tkn)->type);
		ast_add(new_tkn, new_node);
	}
	else if ((*tkn)->type == DBLQUOTE || (*tkn)->type == QUOTE)
	{
		handle_quotes(tkn, buf, env_lst);
		if (*tkn && (*tkn)->right && (*tkn)->right->type == DOLLAR)
		{
			token_lst_remove(tkn);
			token_lst_remove(tkn);
			handle_variables(buf, tkn, env_lst);
			if (*tkn && (*tkn)->type == WHITESPACE && !(*buf))
				add_empty_node(new_tkn);
		}
		if (!(*buf) && *tkn && (!(*tkn)->right || ((*tkn)->right
					&& (*tkn)->right->type != ARG
					&& (*tkn)->right->type != DBLQUOTE)))
			add_empty_node(new_tkn);
	}
}

void	add_new_node(char *buf, t_ast **new_tkn, enum e_type type)
{
	t_ast	*new_node;

	new_node = create_node(ft_strdup(buf), type);
	ast_add(new_tkn, new_node);
	ft_bzero(buf, BUF_SIZE);
}

void	interpreter3(char *buf, t_ast **tkn, t_ast **new_tkn, t_env *env_lst)
{
	if (handle_variables(buf, tkn, env_lst))
		add_new_node(buf, new_tkn, VAR);
	if (((*tkn)->right && (*tkn)->right->type == WHITESPACE && *buf)
		|| !(*tkn)->right)
		add_new_node(buf, new_tkn, VAR);
}

t_ast	*interpreter(t_ast **tkn, t_env *env_lst, char *buf)
{
	t_ast	*new_tkn;

	new_tkn = NULL;
	while (1)
	{
		if (*buf && (!(*tkn) || (*tkn)->type == WHITESPACE || spc_tkn(*tkn)))
			add_new_node(buf, &new_tkn, ARG);
		if (!(*tkn) || (*tkn && (*tkn)->type == SEMICOLON))
			break ;
		if ((*tkn)->type == DOLLAR)
			g_sig.dollar_quote = true;
		if ((*tkn)->type != ARG && (*tkn)->type != VAR && (*tkn)->type != QUEST)
			interpreter2(tkn, &new_tkn, env_lst, buf);
		else if ((*tkn)->type == VAR || (*tkn)->type == QUEST)
			interpreter3(buf, tkn, &new_tkn, env_lst);
		else
			ft_strcat(buf, (*tkn)->value);
		token_lst_remove(tkn);
	}
	return (new_tkn);
}
