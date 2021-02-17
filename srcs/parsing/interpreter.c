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

char	**interpreter_loop(t_ast **token, t_env *env_lst)
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
//	ft_printf("!!%d\n", ac);
	args = calloc(sizeof(char*), (ac + 1));
//	args[ac] = 0;
	while (ptr)
	{
		if (ft_isblank(ptr->value[0]))
		{
			args[i] = ft_strdup(ptr->value);
			i++;
			ptr = ptr->right;
			while (ptr && ft_isblank(ptr->value[0]))
			{
				if (test % 2)
				{
					args[i] = ptr->value;
					i++;
				}
				ptr = ptr->right;
			}
		}
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
			ptr = ptr->right;
			// i++;
			// tmp = ft_strdup("");
			// ptr = ptr->right;
			// while(ptr->value[0] != '\'')
			// {
			// 	tmp = ft_strjoin(tmp, ptr->value);
			// 	if (args[i])
			// 		free(args[i]);
			// 	args[i] = tmp;
			// 	ptr = ptr->right;
			// }
			// ptr = ptr->right;
			// i++;
		}
		else if (ptr->value[0] == '$')
		{
			ptr = ptr->right;
			if (get_env(env_lst, ptr->value))
			{	
				args[i] = ft_strdup(get_env(env_lst, ptr->value));
				i++;
			}
			ptr = ptr->right;
		}
		else if (ptr->value[0] == '>')
		{
			ptr = ptr->right;
			args[i] = ft_strdup(">");
			i++;
		}
		else
		{
			args[i] = ft_strdup(ptr->value);
			ptr = ptr->right;
			i++;
		}
	}
	return (args);
}

void	interpreter(t_state *st, t_ast **token, t_env *env_lst, t_cmd **cmd_lst)
{
	t_ast	*ptr;

	ptr = *token;
	(void)st;
	if (!ft_strncmp(ptr->value, ";", 2))
	{
		ft_putstr_fd("bash: syntax error near unexpected token `;'\n", STDERR);
		return ;
	}
	//(*cmd_lst)->args = ft_split(buf, ' ');
	(*cmd_lst)->args = interpreter_loop(token, env_lst);
	// TODO: split multi commands semicolon in new node cmd_lst
}
