# include "ast.h"

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
	t_ast *node;
	int pos = 0;
	int i = 0;
	char *input = "pwd;ls -l libft;ls $HOME| grep main.c";
	char *tokens[MAXLIST];

	ft_bzero(tokens, MAXLIST);
	if (input)
	{
		node = ft_calloc(1, sizeof(t_ast));
		node->left = NULL;
		node->right = NULL;
		while (input[pos])
		{
			tokens[i] = get_next_token(input, &pos);
			printf("%s\n", tokens[i]);
			ast_add(&node, tokens[i]);
			i++;
		}
	}
	else {
		printf("Usage: ./a.out <args>\n");
	}
	return (0);
}