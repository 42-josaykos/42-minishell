/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpascal <alpascal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 11:09:10 by jonny             #+#    #+#             */
/*   Updated: 2021/05/25 17:50:52 by alpascal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/msh.h"

/*
** Iterate through the input from the pos index and check each character.
** Returns the fisrt token it finds and move the pos index at the start of
** the next token
*/

static bool	is_special_tkn(char c)
{
	if (c == ';' || c == '|' || c == '>'
		|| c == '<' || c == '$' || c == '\''
		|| c == '\"' || c == '\\' || c == ' '
		|| c == '\t' || c == '?')
		return (true);
	return (false);
}

bool	is_append_tkn(char *input, int pos)
{
	if (input[pos] == '>' && input[pos + 1] == '>')
		return (true);
	return (false);
}

char	*get_special_tkn(char *input, int *pos)
{
	char	*token;

	if (is_append_tkn(input, *pos))
	{
		token = ft_calloc(3, sizeof(char));
		token[0] = input[*pos];
		token[1] = input[*pos + 1];
		(*pos) += 2;
		return (token);
	}
	token = ft_calloc(2, sizeof(char));
	token[0] = input[*pos];
	(*pos)++;
	return (token);
}

char	*get_next_token(char *input, int *pos)
{
	int		start;
	char	*token;

	start = *pos;
	if (is_special_tkn(input[*pos]))
		return (get_special_tkn(input, pos));
	while (input[*pos] || ft_isblank(input[*pos]))
	{
		if (ft_isblank(input[*pos]) || input[*pos] == ';' || input[*pos] == '|'
			|| input[*pos] == '|' || input[*pos] == '>' || input[*pos] == '<'
			|| input[*pos] == '$' || input[*pos] == '\'' || input[*pos] == '\"'
			|| input[*pos] == '\\' || input[*pos] == '?')
		{
			token = ft_substr(input, start, *pos - start);
			return (token);
		}
		(*pos)++;
	}
	token = ft_substr(input, start, *pos);
	return (token);
}
