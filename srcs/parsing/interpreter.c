#include "../../includes/msh.h"
#include <linux/limits.h>

int	token_lst_size(t_ast *token)
{
	int		count;
	t_ast	*tmp;

	count = 0;
	tmp = token;
	if (!token)
		return (0);
	while (tmp)
	{
		count++;
		tmp = tmp->right;
	}
	return (count);
}

void	concat_buffer(t_ast **ptr, t_env *env_lst, char **arg, char *buffer)
{
	if ((*ptr)->type == VARIABLE)
		ft_strcat(buffer, get_env(env_lst, (*ptr)->value));
	else if ((*ptr)->type == ARG || (*ptr)->type == WHITESPACE)
		ft_strcat(buffer, (*ptr)->value);
	*ptr = (*ptr)->right;
	if (!(*ptr))
		*arg = ft_strdup(buffer);
}

void	create_new_arg(t_ast **ptr, char **arg, char *buffer)
{
	(void)ptr;
	*arg = ft_strdup(buffer);
	ft_bzero(buffer, BUF_SIZE);
}

void	handle_dblquote(t_ast **ptr, t_state *st, t_env *env_lst, char **arg)
{
	char	buffer[BUF_SIZE];

	ft_bzero(buffer, BUF_SIZE);
	while (*ptr)
	{
		if ((*ptr)->type == DBLQUOTE)
		{
			st->dblquote++;
			*ptr = (*ptr)->right;
		}
		if (!(st->dblquote % 2) && (!(*ptr) || (*ptr)->type == WHITESPACE
			|| (*ptr)->type == SEMICOLON || (*ptr)->type == PIPE))
		{
			create_new_arg(ptr, arg, buffer);
			break ;
		}
		else if (*ptr && ((*ptr)->type == ESCAPE || (*ptr)->type == DOLLAR))
		{
			*ptr = (*ptr)->right;
			continue ;
		}
		else if (*ptr)
			concat_buffer(ptr, env_lst, arg, buffer);
	}
}

t_ast *interpreter(t_state *st, t_ast *token, t_env *env_lst)
{
	char *buffer[BUF_SIZE];
	int i;
	t_ast *new_node = NULL;
	t_ast *new_token = NULL;

	i = 0;
	ft_bzero(buffer, BUF_SIZE);
	while (token)
	{
		if (token->type == DBLQUOTE)
		{
			handle_dblquote(&token, st, env_lst, &buffer[i]);
			new_node = create_node(buffer[i], ARG);
			ast_add(&new_token, new_node);
			i++;
		}
		if (token && token->type != WHITESPACE && token->type != ESCAPE)
		{
			buffer[i] = ft_strdup(token->value);
			new_node = create_node(buffer[i], token->type);
			ast_add(&new_token, new_node);
			i++;
		}
		if (token)
			token = token->right;
	}
	return (new_token);
}