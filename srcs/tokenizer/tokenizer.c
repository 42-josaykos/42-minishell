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
		|| c == '\t')
		return (true);
	return (false);
}

char	*get_next_token(char *input, int *pos)
{
	int		start;
	char	*token;

	start = *pos;
	if (is_special_tkn(input[*pos]))
	{
		token = ft_calloc(2, sizeof(char));
		token[0] = input[*pos];
		(*pos)++;
		return (token);
	}
	while (input[*pos] || ft_isblank(input[*pos]))
	{
		if (ft_isblank(input[*pos]) || input[*pos] == ';' || input[*pos] == '|'
			|| input[*pos] == '|' || input[*pos] == '>' || input[*pos] == '<'
			|| input[*pos] == '$' || input[*pos] == '\'' || input[*pos] == '\"'
			|| input[*pos] == '\\')
		{
			token = ft_substr(input, start, *pos - start);
			return (token);
		}
		(*pos)++;
	}
	token = ft_substr(input, start, *pos);
	return (token);
}
