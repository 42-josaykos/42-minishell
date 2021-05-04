/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 11:09:01 by jonny             #+#    #+#             */
/*   Updated: 2021/05/04 17:03:19 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/msh.h"

/*
** Add new token node at the end of the token list
*/

void	ast_add(t_ast **token, t_ast *new_node)
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

t_ast	*create_node(char *buffer, enum e_type type)
{
	t_ast	*new_node;

	new_node = ft_calloc(1, sizeof(t_ast));
	new_node->type = type;
	new_node->right = NULL;
	new_node->value = buffer;
	return (new_node);
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
		new_node = create_node(buffer[i], ARG);
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
