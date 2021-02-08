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

int main(int argc, char **argv)
{
	t_ast *node;
	int pos = 0;
	int i = 0;
	// char *input = "pwd;ls -l libft;ls $HOME| grep main.c";
	char *tokens[MAXLIST];

	ft_bzero(tokens, MAXLIST);
	if (argc == 2)
	{
		node = ft_calloc(1, sizeof(t_ast));
		node->left = NULL;
		node->right = NULL;
		node->parent = NULL;
		while (argv[1][pos])
		{
			tokens[i] = get_next_token(argv[1], &pos);
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