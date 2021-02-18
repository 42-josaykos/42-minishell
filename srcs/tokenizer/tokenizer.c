#include "../../includes/msh.h"

/*
** Iterate through the input from the pos index and check each character.
** Returns the fisrt token it finds and move the pos index at the start of
** the next token
*/

char	*get_next_token(char *input, int *pos)
{
	int		start;
	char	*token;

	start = *pos;
	if (input[*pos] == ';' || input[*pos] == '|' || input[*pos] == '>'
		|| input[*pos] == '<' || input[*pos] == '$' || input[*pos] == '\''
		|| input[*pos] == '\"' || input[*pos] == '\\' || input[*pos] == ' '
		|| input[*pos] == '\t')
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

// int main(void)
// {
// 	t_ast *token = NULL;
// 	int pos = 0;
// 	int i = 0;
// 	// char *input = "echo            \"     salut\""; // segfault
// 	char *buffer[MAXCHAR];

// 	while (i < MAXCHAR)
// 	{
// 		buffer[i] = NULL;
// 		i++;
// 	}
// 	i = 0;
// 	if (input)
// 	{
// 		while (input[pos])
// 		{
// 			buffer[i] = get_next_token(input, &pos);
// 			// printf("tokens[%d] = \"%s\"\n", i, buffer[i]);
// 			i++;
// 		}
// 		ast_init(&token, buffer);
// 		for(int j = 0; token->right != NULL ; token = token->right)
// 			printf("token[%d] = \"%s\"\n", j++, token->value);
// 		free_ast(&token);
// 	}
// 	else {
// 		printf("Usage: ./a.out <args>\n");
// 	}
// 	return (0);
// }
