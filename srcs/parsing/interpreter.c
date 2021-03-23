/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 11:07:31 by jonny             #+#    #+#             */
/*   Updated: 2021/03/23 16:17:39 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/msh.h"

void	handle_variables(char *buf, t_ast *token, t_env *env_lst)
{
	char	*tmp;

	tmp = NULL;
	if (token->type == VARIABLE)
	{
		tmp = get_env(env_lst, token->value);
		if (tmp != NULL)
			ft_strcat(buf, tmp);
	}
	else if (token->type == QUESTION)
	{
		if (token->left && token->left->type == DOLLAR)
		{
			tmp = ft_itoa(g_sig.exit_status);
			ft_strcat(buf, tmp);
			free(tmp);
		}
		else
			ft_strcat(buf, token->value);
	}
}

void	handle_quotes(t_ast **token, char *buf, t_env *env_lst)
{
	enum e_type	type;

	if (*token)
	{
		type = (*token)->type;
		*token = (*token)->right;
	}
	while (*token && (*token)->type != type)
	{
		if (type == DBLQUOTE)
		{
			if ((*token)->type == VARIABLE || (*token)->type == QUESTION)
				handle_variables(buf, *token, env_lst);
			else if ((*token)->type != DOLLAR && (*token)->type != ESCAPE)
				ft_strcat(buf, (*token)->value);
		}
		else
			ft_strcat(buf, (*token)->value);
		*token = (*token)->right;
	}
}

static bool	spc_tkn(t_ast *tkn)
{
	if (tkn->type == SEMICOLON || tkn->type == PIPE
		|| tkn->type == REDIR || tkn->type == APPEND
		|| tkn->type == INPUT)
		return (true);
	return (false);
}

void	interpreter2(t_ast **tkn, t_ast **new_tkn, t_env *env_lst, char *buf)
{
	t_ast	*new_node;

	if (spc_tkn(*tkn))
	{
		new_node = create_node(ft_strdup((*tkn)->value), (*tkn)->type);
		ast_add(new_tkn, new_node);
	}
	else if ((*tkn)->type == DBLQUOTE || (*tkn)->type == QUOTE)
		handle_quotes(tkn, buf, env_lst);
	else if ((*tkn)->type == VARIABLE || (*tkn)->type == QUESTION)
		handle_variables(buf, *tkn, env_lst);
}

t_ast	*interpreter(t_ast *tkn, t_env *env_lst)
{
	t_ast	*new_tkn;
	t_ast	*new_node;
	char	buf[BUF_SIZE];

	new_tkn = NULL;
	ft_bzero(buf, BUF_SIZE);
	while (1)
	{
		if ((!tkn || tkn->type == WHITESPACE || spc_tkn(tkn)))
		{
			new_node = create_node(ft_strdup(buf), ARG);
			ast_add(&new_tkn, new_node);
			ft_bzero(buf, BUF_SIZE);
		}
		if (!tkn)
			break ;
		if (tkn->type != ARG)
			interpreter2(&tkn, &new_tkn, env_lst, buf);
		else
			ft_strcat(buf, tkn->value);
		if (tkn)
			tkn = tkn->right;
	}
	return (new_tkn);
}
