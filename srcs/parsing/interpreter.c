#include "../../includes/msh.h"

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

void	concat_buffer(t_ast **ptr, t_env *env_lst, char *buffer)
{
	if ((*ptr)->type == VARIABLE)
		ft_strcat(buffer, get_env(env_lst, (*ptr)->value));
	else if ((*ptr)->type == ARG || (*ptr)->type == WHITESPACE)
		ft_strcat(buffer, (*ptr)->value);
	*ptr = (*ptr)->right;
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
		if (!(st->dblquote % 2) && (!(*ptr) || (*ptr)->type == WHITESPACE))
		{
			*arg = ft_strdup(buffer);
			ft_bzero(buffer, BUF_SIZE);
			if (*ptr)
				*ptr = (*ptr)->right;
			break ;
		}
		else if (*ptr && ((*ptr)->type == ESCAPE || (*ptr)->type == DOLLAR))
		{
			*ptr = (*ptr)->right;
			continue ;
		}
		else if (*ptr)
			concat_buffer(ptr, env_lst, buffer);
		if (!(*ptr))
			*arg = ft_strdup(buffer);
	}
}

char **interpreter(t_state *st, t_ast *token, t_env *env_lst)
{
	char **args;
	int i;

	args = calloc(sizeof(char *), token_lst_size(token) + 1);
	i = 0;
	while (token && args)
	{
		if (token->type == DBLQUOTE)
		{
			handle_dblquote(&token, st, env_lst, &args[i]);
			i++;
		}
		else if (token->type != WHITESPACE)
		{
			args[i] = ft_strdup(token->value);
			i++;
		}
		if (token)
			token = token->right;
	}
	return (args);
}