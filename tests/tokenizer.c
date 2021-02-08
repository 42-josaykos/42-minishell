# include "../includes/msh.h"
#include <ctype.h>
#include <stdio.h>

enum e_type {
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

typedef struct s_ast {
	enum e_type	type;
	char	*value;
	struct s_ast	*parent;
	struct s_ast	*left;
	struct s_ast	*right;
}				t_ast;

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

	token = NULL;
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

void ast_add(t_ast **node, char *token)
{
	t_ast *new = NULL;
	t_ast *next_parent;
	t_ast *tmp;
	t_ast *ptr;

	ptr = *node;
	if (!ptr->left && !ptr->right && !ptr->parent) // start new tree from the left side
	{
		new = ft_calloc(1, sizeof(t_ast));
		new->type = BUILTIN;
		new->value = token;
		new->left = NULL;
		new->right = NULL;

		next_parent = ft_calloc(1, sizeof(t_ast)); // create next parent node (top)
		next_parent->left = new; // link parent to his left child
		new->parent = next_parent; // link child node to his parent

		ptr = new;
		*node = ptr;

	}
	else if (!ptr->right && ptr->left) // add right child to the parent node (top)
	{
		ptr = ptr->right;
		ptr = ft_calloc(1, sizeof(t_ast));
		ptr->type = EXEC;
		ptr->value = token;
		ptr->left = NULL;
		ptr->right = NULL;
		ptr->parent = *node;
		(*node)->right = ptr;
		return ;
	}
	else // new parent
	{
		while (ptr->parent)
		{
			tmp = ptr;
			ptr = ptr->parent;
		}
		// new = ft_calloc(1, sizeof(t_ast));
		ptr->type = SEMICOLON;
		ptr->value = token;
		ptr->left = tmp;
		ptr->right = NULL;
		ptr->parent = ft_calloc(1, sizeof(t_ast));
		// ptr = new;
		*node = ptr;
		return ;
	}
	return ;
}

int main(void)
{
	t_ast *node;
	int pos = 0;
	int i = 0;
	char *input = "pwd;ls -l libft;ls$HOME| grep main.c";
	char *tokens[MAXLIST];

	ft_bzero(tokens, MAXLIST);
	if (input)
	{
		node = ft_calloc(1, sizeof(t_ast));
		node->left = NULL;
		node->right = NULL;
		node->parent = NULL;
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