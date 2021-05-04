/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 11:07:31 by jonny             #+#    #+#             */
/*   Updated: 2021/05/04 16:58:15 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/msh.h"

void		handle_variables(char *buf, t_ast *token, t_env *env_lst)
{
	char	*tmp;

	(void)env_lst;
	tmp = NULL;
	if (token->type == VAR)
	{
		tmp = get_env(env_lst, token->value);
		if (tmp != NULL)
			ft_strcat(buf, tmp);
	}
	else if (token->type == QUEST)
	{
		if (g_sig.dollar_quote)
		{
			tmp = ft_itoa(g_sig.exit_status);
			ft_strcat(buf, tmp);
			free(tmp);
		}
		else
			ft_strcat(buf, token->value);
	}
	g_sig.dollar_quote = false;
}

static bool	spc_tkn(t_ast *tkn)
{
	if (tkn->type == SEMICOLON || tkn->type == PIPE
		|| tkn->type == REDIR || tkn->type == APPEND
		|| tkn->type == INPUT)
		return (true);
	return (false);
}

void		interpreter2(t_ast **tkn, t_ast **new_tkn, t_env *env_lst,
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
		g_sig.dollar_quote = false;
		if (!(*buf) && (!(*tkn)->right || ((*tkn)->right
					&& (*tkn)->right->type != ARG)))
		{
			new_node = create_node(ft_strdup(""), ARG);
			ast_add(new_tkn, new_node);
		}
	}
}

static void	add_new_node(char *buf, t_ast **new_tkn, enum e_type type)
{
	t_ast	*new_node;

	new_node = create_node(ft_strdup(buf), type);
	ast_add(new_tkn, new_node);
	ft_bzero(buf, BUF_SIZE);
}

t_ast		*interpreter(t_ast **tkn, t_env *env_lst)
{
	t_ast	*new_tkn;
	char	buf[BUF_SIZE];

	new_tkn = NULL;
	ft_bzero(buf, BUF_SIZE);
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
		{
			handle_variables(buf, *tkn, env_lst);
			add_new_node(buf, &new_tkn, VAR);
		}
		else
			ft_strcat(buf, (*tkn)->value);
		token_lst_remove(tkn);
	}
	return (new_tkn);
}
