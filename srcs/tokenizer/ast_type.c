/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_type.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 14:22:53 by jonny             #+#    #+#             */
/*   Updated: 2021/03/04 15:11:19 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/msh.h"

void	set_type(t_ast *ptr, enum e_type type)
{
	if (ptr->left && ptr->left->type != ESCAPE)
		ptr->type = type;
}

static void	set_redir_append(t_ast *ptr)
{
	if (ptr->left && ptr->left->type != ESCAPE && ptr->left->type != REDIR)
		ptr->type = REDIR;
	else if (ptr->left && ptr->left->type == REDIR)
	{
		ptr->left->type = APPEND;
		ptr->type = APPEND;
	}
}

static void	set_escape(t_ast *ptr)
{
	if (ptr->right && (ptr->right->value[0] == '$' ||
	ptr->right->value[0] == '\"' || ptr->right->value[0] == '\'' ||
	ptr->right->value[0] == '>' || ptr->right->value[0] == '<' ||
	ptr->right->value[0] == '\\'))
		set_type(ptr, ESCAPE);
}

static void	set_whitespace(t_ast *ptr)
{
	ptr->type = WHITESPACE;
}

static void	ast_check_type2(t_ast *ptr)
{
	if (ptr->value[0] == '\'')
		set_type(ptr, QUOTE);
	else if (ptr->value[0] == '\"')
		set_type(ptr, DBLQUOTE);
	else if (ptr->value[0] == '<')
		set_type(ptr, INPUT);
	else if (ptr->value[0] == '>')
		set_redir_append(ptr);
	else if (ptr->left && ptr->left->type == DOLLAR)
		ptr->type = VARIABLE;
}

void	ast_check_type(t_ast **token)
{
	t_ast	*ptr;

	ptr = *token;
	while (ptr)
	{
		if (ptr->value[0] == '\\')
			set_escape(ptr);
		else if (ptr->value[0] == ' ' || ptr->value[0] == '\t')
			set_whitespace(ptr);
		else if (ptr->value[0] == '$')
			set_type(ptr, DOLLAR);
		else if (ptr->value[0] == ';')
			set_type(ptr, SEMICOLON);
		else if (ptr->value[0] == '|')
			set_type(ptr, PIPE);
		else
			ast_check_type2(ptr);
		ptr = ptr->right;
	}
}
