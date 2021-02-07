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

void get_next_token(char *input)
{
	int pos;

	pos = 0;
	while (input[pos] != 0)
	{
		if (isblank(input[pos]))
		{
			while (input[pos] && isblank(input[pos]))
			{
				pos++;
			}
		}
		printf("%c\n", input[pos]);
		pos++;
	}
}

int main(void)
{
	t_token *tkn;
	char *input = "ls -l srcs ; pwd";

	if (input)
	{
		tkn = ft_calloc(1, sizeof(t_token));
		get_next_token(input);
		free(tkn);
	}
	else {
		printf("Usage: ./a.out <args>\n");
	}
	return (0);
}