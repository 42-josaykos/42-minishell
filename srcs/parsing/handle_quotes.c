/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 17:38:04 by jonny             #+#    #+#             */
/*   Updated: 2021/03/26 18:43:46 by jonny            ###   ########.fr       */
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

void 	handle_quotes2(t_ast **token, char *buf, bool dollar_sign)
{
	char	*ptr;
	char	*str;
	char	c;

	ptr = NULL;
	str = "\0";
	if ((*token)->value[0] == '\\' && (*token)->right && dollar_sign)
	{
		c = (*token)->right->value[0];
		if (is_ansi_c_quoting(&str, c))
		{
			ft_strcat(buf, str);
			*token = (*token)->right;
			ptr = &(*token)->value[1];
			ft_strcat(buf, ptr);
		}
		else
			ft_strcat(buf, (*token)->value);
	}
	else
		ft_strcat(buf, (*token)->value);
}
