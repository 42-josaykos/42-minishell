#include "ast.h"

void ast_add(t_ast **node, char *token)
{
	t_ast *new = NULL;
	t_ast *next_node;
	t_ast *tmp;
	t_ast *ptr;

	ptr = *node;
	if (!ptr->left && !ptr->right) // start new tree from the left side
	{
		new = ft_calloc(1, sizeof(t_ast));
		new->type = BUILTIN;
		new->value = token;
		new->left = NULL;

		ptr = new;
		next_node = ft_calloc(1, sizeof(t_ast)); // create next empty node (right)
		next_node->left = new; // link next empty node to his previous node (left)
		new->right = next_node; // link node to the next empty node (right)

		*node = ptr;

	}
	else // new node
	{
		while (ptr->right)
		{
			tmp = ptr;
			ptr = ptr->right;
		}
		ptr->type = SEMICOLON;
		ptr->value = token;
		ptr->left = tmp;
		ptr->right = ft_calloc(1, sizeof(t_ast));
		*node = ptr;
		return ;
	}
	return ;
}