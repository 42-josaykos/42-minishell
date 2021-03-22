/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 11:07:31 by jonny             #+#    #+#             */
/*   Updated: 2021/03/22 15:51:20 by jonny            ###   ########.fr       */
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

t_ast	*interpreter(t_ast *token, t_env *env_lst)
{
	t_ast	*new_token;
	t_ast	*new_node;
	char	buf[BUF_SIZE];

	new_token = NULL;
	ft_bzero(buf, BUF_SIZE);
	while (1)
	{
		if (!is_empty(buf) && (!token || token->type == WHITESPACE
				|| token->type == SEMICOLON || token->type == PIPE
				|| token->type == REDIR || token->type == APPEND
				|| token->type == INPUT))
		{
			new_node = create_node(ft_strdup(buf), ARG);
			ast_add(&new_token, new_node);
			ft_bzero(buf, BUF_SIZE);
		}
		if (!token)
			break ;
		if (token->type == SEMICOLON || token->type == PIPE
			|| token->type == REDIR || token->type == APPEND
			|| token->type == INPUT)
		{
			new_node = create_node(ft_strdup(token->value), token->type);
			ast_add(&new_token, new_node);
		}
		else if (token->type == DBLQUOTE || token->type == QUOTE)
			handle_quotes(&token, buf, env_lst);
		else if (token->type == VARIABLE || token->type == QUESTION)
			handle_variables(buf, token, env_lst);
		else if (token->type == ARG)
			ft_strcat(buf, token->value);
		if (token)
			token = token->right;
	}
	return (new_token);
}
