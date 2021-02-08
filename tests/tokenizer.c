# include "ast.h"
#include <stdio.h>
#include <stdlib.h>

char * get_next_token(char *input, int *pos)
{
	int start;
	char *token;

	while (input[*pos] && isblank(input[*pos]))
		(*pos)++;
	start = *pos;
	if (input[*pos] == ';' || input[*pos] == '|')
	{
		token = ft_calloc(2, sizeof(char));
		token[0] = input[*pos];
		(*pos)++;
		return token;
	}
	while (input[*pos] || isblank(input[*pos]))
	{
		if (isblank(input[*pos]) || input[*pos] == ';' || input[*pos] == '|')
		{
			token = ft_substr(input, start, *pos - start);
			return token;
		}
		(*pos)++;
	}
	token = ft_substr(input, start, *pos);
	return token;
}

int main(void)
{
	t_ast *token = NULL;
	int pos = 0;
	int i = 0;
	char *input = "pwd;ls -l libft;ls $HOME| grep main.c";
	char *buffer[MAXLIST];

	ft_bzero(buffer, MAXLIST);
	if (input)
	{
		while (input[pos])
		{
			buffer[i] = get_next_token(input, &pos);
			// printf("%s\n", tokens[i]);
			i++;
		}
		ast_init(&token, buffer);
		// for(; token->right != NULL ; token = token->right)
			// printf("%s\n", token->value);
		free_ast(&token);
	}
	else {
		printf("Usage: ./a.out <args>\n");
	}
	return (0);
}