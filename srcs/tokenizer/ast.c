#include "../../includes/msh.h"

/*
** Add new token node at the end of the token list 
*/

static void	ast_add(t_ast **token, t_ast *new_node)
{
	t_ast	*tmp;

	tmp = *token;
	if (!(*token))
		*token = new_node;
	else
	{
		while ((*token)->right != NULL)
			*token = (*token)->right;
		(*token)->right = new_node;
		new_node->left = *token;
		*token = tmp;
	}
}

/*
** Create a new node and set the value and type of the token
*/

static t_ast	*create_node(char *buffer)
{
	t_ast	*new_node;

	new_node = malloc(sizeof(t_ast));
	new_node->type = ARG;
	new_node->right = NULL;
	new_node->value = buffer;
	return (new_node);
}

void	ast_check_type(t_ast **token)
{
	t_ast *ptr;

	ptr = *token;
	while (ptr)
	{
		if (ptr->value[0] == '\\')
		{
			if (ptr->left && ptr->left->type != ESCAPE)
				ptr->type = ESCAPE;
		}
		else if (ptr->value[0] == ' ')
		{
			if (ptr->left && ptr->left->type != ESCAPE)
				ptr->type = WHITESPACE;
		}
		else if (ptr->value[0] == '$')
		{
			if (ptr->left && ptr->left->type != ESCAPE)
				ptr->type = DOLLAR;
		}
		else if (ptr->left && ptr->left->type == DOLLAR)
			ptr->type = VARIABLE;
		ptr = ptr->right;
	}
	return ;
}

/*
** Iterate in the buffered list, and create a new node for
** each token from the list
*/

void	ast_init(t_ast **token, char **buffer)
{
	t_ast	*new_node;
	int		i;

	i = 0;
	while (buffer[i])
	{
		new_node = create_node(buffer[i]);
		ast_add(token, new_node);
		i++;
	}
	ast_check_type(token);
}

/*
** Iterate in the token list, free buffered value and free each node till empty
*/

void	free_ast(t_ast **token)
{
	t_ast	*ptr;
	t_ast	*tmp;

	ptr = *token;
	while (ptr)
	{
		tmp = ptr->right;
		if (ptr->value)
			free(ptr->value);
		free(ptr);
		ptr = tmp;
	}
	*token = NULL;
}
