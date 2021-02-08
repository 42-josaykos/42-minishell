#ifndef AST_H
# define AST_H

# include "../../includes/msh.h"

enum	e_type
{
	END,
	BUILTIN,
	EXEC,
	ARG,
	VAR,
	QUOTE,
	DBL_QUOTE,
	SEMICOLON,
	PIPE,
	L_CHEVRON,
	R_CHEVRON,
	DBL_CHEVRON,
	BACKSLASH,
};

typedef struct s_ast
{
	enum e_type		type;
	char			*value;
	struct s_ast	*left;
	struct s_ast	*right;
}				t_ast;

void	ast_init(t_ast **token, char **buffer);
void	free_ast(t_ast **token);
char	*get_next_token(char *input, int *pos);

#endif