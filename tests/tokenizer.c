# include "../includes/msh.h"
#include <ctype.h>

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
	char *current_tkn;
	char *current_char;
	char *tkn;
	int i;
	int j;

	current_char = input;
	current_tkn = input;
	i = 0;
	j = 0;
	while(1)
	{
		if (isblank(current_char[i]) || current_char[i] == 0)
		{
			tkn = ft_substr(current_tkn, 0, j);
			if (current_char[i] == '\0')
				break ;
			ft_printf("tkn = '%s'\n", tkn);
			current_tkn += i;
			while (isblank(current_char[i]))
			{
				current_tkn++;
				i++;
			}
			j = 0;
			j++;
			continue ;
		}
		ft_printf("current_char = '%c'\n", current_char[i]);
		i++;
		j++;
	}
	tkn = ft_strdup(current_tkn);
	ft_printf("tkn = '%s'\n", tkn);
	return ;
}

int main(void)
{
	t_token *tkn;
	char *input = "ls -l srcs";

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