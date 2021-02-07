# include "../includes/msh.h"
#include <ctype.h>
#include <stdio.h>

enum e_type {
	BUILTIN,
	EXEC,
	EQUALS,
	ARG,
	SLASH,
	L_CHEVRON,
	R_CHEVRON,
	DBL_CHEVRON,
	SEMICOLON,
	PIPE,
	DOLLAR,
	BACKSLASH,
	QUOTE,
	DBL_QUOTE,
	END
};

typedef struct s_token {
	enum e_type type;
	char *value;
	struct s_token *up;
	struct s_token *left;
	struct s_token *right;
}				t_token;

// static void error()
// {
	// ft_putstr_fd("Error parsing input\n", 2);
// }

// 0123456789
// ls -l srcs

char * get_next_token(char *input, int *pos)
{
	int start;
	char *token;

	while (input[*pos] && isblank(input[*pos]))
		(*pos)++;
	start = *pos;
	while (input[*pos] != 0 || isblank(input[*pos]))
	{
		if (isblank(input[*pos]))
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
	t_token *tkn;
	int pos = 0;
	char *input = "				ls -l srcs ;     pwd";
	char *token;

	token = NULL;
	if (input)
	{
		tkn = ft_calloc(1, sizeof(t_token));
		while (input[pos])
		{
			token = get_next_token(input, &pos);
			printf("%s\n", token);
			free(token);
		}
		free(tkn);
	}
	else {
		printf("Usage: ./a.out <args>\n");
	}
	return (0);
}