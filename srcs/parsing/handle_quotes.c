/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 17:38:04 by jonny             #+#    #+#             */
/*   Updated: 2021/06/01 12:54:39 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/msh.h"

/*
** https://www.gnu.org/software/bash/manual/bash.html#ANSI_002dC-Quoting
*/

bool	is_ansi_c_quoting2(char **str, char c)
{
	if (c == 'r')
		*str = "\r";
	else if (c == 't')
		*str = "\t";
	else if (c == 'v')
		*str = "\v";
	else if (c == '\\')
		*str = "\\";
	else if (c == '\'')
		*str = "\'";
	else if (c == '\"')
		*str = "\"";
	else if (c == '\?')
		*str = "\?";
	if (!ft_strlen(*str))
		return (false);
	return (true);
}

bool	is_ansi_c_quoting(char **str, char c)
{
	if (c == 'a')
		*str = "\a";
	else if (c == 'b')
		*str = "\b";
	else if (c == 'e')
		*str = "\e";
	else if (c == 'E')
		*str = "\E";
	else if (c == 'f')
		*str = "\f";
	else if (c == 'n')
		*str = "\n";
	return (is_ansi_c_quoting2(str, c));
}

static void	handle_quotes2(t_ast **token, char *buf)
{
	char	*ptr;
	char	*str;
	char	c;

	ptr = NULL;
	str = "\0";
	if ((*token)->value[0] == '\\' && (*token)->right && g_sig.dollar_quote)
	{
		c = (*token)->right->value[0];
		if (is_ansi_c_quoting(&str, c))
		{
			ft_strcat(buf, str);
			token_lst_remove(token);
			ptr = &(*token)->value[1];
			ft_strcat(buf, ptr);
		}
		else
			ft_strcat(buf, (*token)->value);
	}
	else if ((*token)->value[0] != '\'')
		ft_strcat(buf, (*token)->value);
}

int	handle_first_quote(t_ast **token, char *buf,
														enum e_type *type)
{
	int	len;

	len = ft_strlen(buf);
	if (*token)
	{
		*type = (*token)->type;
		if (buf[len - 1] == '=')
		{
			ft_strcat(buf, (*token)->value);
			token_lst_remove(token);
			return (1);
		}
		else
			token_lst_remove(token);
	}
	return (0);
}

void	handle_quotes(t_ast **token, char *buf, t_env *env_lst)
{
	enum e_type	type;

	type = QUOTE;
	handle_first_quote(token, buf, &type);
	while (*token)
	{
		if (type == DBLQUOTE)
		{
			if ((*token)->type == VAR || (*token)->type == QUEST)
				handle_variables_quotes(buf, token, env_lst);
			else if ((*token)->type == ESCAPE && (*token)->right
				&& (*token)->right->value[0] == '\'')
				ft_strcat(buf, (*token)->value);
			else if ((*token)->type != DOLLAR
				&& (g_sig.dollar_quote || (*token)->type != ESCAPE)
				&& (*token)->type != DBLQUOTE)
				ft_strcat(buf, (*token)->value);
		}
		else if (type == QUOTE)
			handle_quotes2(token, buf);
		if ((*token)->type == type)
			break ;
		token_lst_remove(token);
	}
	g_sig.dollar_quote = false;
}
