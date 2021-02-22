#include "../../includes/msh.h"

int	arg_count(t_ast **token)
{
	int		ac;
	t_ast	*ptr;
	int		test;

	test = 0;
	ptr = *token;
	ac = 0;
	while (ptr)
	{
		if (ft_isblank(ptr->value[0]))
		{
			ac++;
			while (ptr && ptr->value && ft_isblank(ptr->value[0]))
			{
				ptr = ptr->right;
				if (test % 2)
					ac++;
			}
		}
		else if (ptr->value[0] == '\'')
		{
			ac++;
			while (ptr->value && ptr->value[0] != '\'')
				ptr = ptr->right;
			ptr = ptr->right;
		}
		else if (ptr->value[0] == '\"')
		{
			if (test % 2)
				ac++;
			test++;
			// while (ptr->value && ptr->value[0] != '\"')
			// 	ptr = ptr->right;
			 ptr = ptr->right;
		}
		else if (ptr->value[0] == '$')
		{
			ac ++;
			ptr = ptr->right;
		}
		else if (ptr->value[0] == '>')
		{
			ac++;
			ptr = ptr->right;
			if (ptr->value[0] == '>')
				ptr = ptr->right;
		}
		else
		{
			ac++;
			ptr = ptr->right;
		}
	}
//	printf("%d\n", ac);
	return (ac);
}

void handle_dquotes(t_ast **ptr, t_state *st, char **arg)
{
	char buffer[BUF_SIZE];

	ft_bzero(buffer, BUF_SIZE);
	while (*ptr)
	{
		if ((*ptr)->value[0] == '\"')
		{
			st->dbl_quotes++;
			*ptr = (*ptr)->right;
		}
		if (!(st->dbl_quotes % 2) && (!(*ptr) || (*ptr)->value[0] == ' '))
		{
			*arg = ft_strdup(buffer);
			ft_bzero(buffer, BUF_SIZE);
			if (*ptr)
				*ptr = (*ptr)->right;
			break ;
		}
		else if (*ptr && (*ptr)->value[0] == '\"')
			continue ;
		else if (*ptr)
		{
			ft_strcat(buffer, (*ptr)->value);
			*ptr = (*ptr)->right;
			if (!(*ptr))
				*arg = ft_strdup(buffer);
		}
	}
}

char	**interpreter_loop(t_state *st,t_ast **token, t_env *env_lst)
{
	int		ac;
	int		i;
	int		test;
	char	*tmp;
	char	**args;
	t_ast	*ptr;
	test = 0;
	i = 0;
	ptr = *token;
	ac = arg_count(token);
	args = calloc(sizeof(char*), (ac + 1));
	while (ptr)
	{
		if (ft_isblank(ptr->value[0]))
			ptr = ptr->right;
		else if (ptr->value[0] == '\'')
		{
			tmp = ft_strdup("");
			ptr = ptr->right;
			while (ptr->value[0] != '\'')
			{
				tmp = ft_strjoin(tmp, ptr->value);
				if (args[i])
					free(args[i]);
				args[i] = tmp;
				ptr = ptr->right;
			}
			ptr = ptr->right;
			i++;
		}
		else if (ptr->value[0] == '\"')
		{
			handle_dquotes(&ptr, st, &args[i]);
			i++;
		}
		else if (ptr && ptr->value[0] == '$')
		{
			ptr = ptr->right;
			if (get_env(env_lst, ptr->value))
			{	
				args[i] = ft_strdup(get_env(env_lst, ptr->value));
				i++;
			}
			ptr = ptr->right;
		}
		else if (ptr && ptr->value[0] == '>')
		{
			ptr = ptr->right;
			args[i] = ft_strdup(">");
			i++;
		}
		else if (ptr)
		{
			args[i] = ft_strdup(ptr->value);
			ptr = ptr->right;
			i++;
		}
	}
	return (args);
}
