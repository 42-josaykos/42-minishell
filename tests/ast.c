#include "ast.h"

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
		ptr->type = SEMICOLON;
		ptr->value = token;
		ptr->left = tmp;
		ptr->right = NULL;
		ptr->parent = ft_calloc(1, sizeof(t_ast));
		*node = ptr;
		return ;
	}
	return ;
}