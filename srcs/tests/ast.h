#ifndef AST_H
# define AST_H

# include "../../includes/msh.h"





void	ast_init(t_ast **token, char **buffer);
void	free_ast(t_ast **token);
char	*get_next_token(char *input, int *pos);

#endif