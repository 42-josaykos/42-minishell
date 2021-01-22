#include "../../includes/msh.h"

/*
**	look for the value of a specified key
*/

char	*get_env(t_env *env_lst, char *key)
{
	while (env_lst)
	{
		if (!ft_strncmp(env_lst->key, key, ft_strlen(key)))
		{
			return (env_lst->value);
		}
		env_lst = env_lst->next;
	}
	return (NULL);
}

void	cmd_lst_add(t_cmd **cmd_lst, t_cmd *new_cmd)
{
	t_cmd	*tmp;

	if (cmd_lst != NULL)
	{
		if (*cmd_lst == NULL)
			*cmd_lst = new_cmd;
		else
		{
			tmp = *cmd_lst;
			while (tmp->next != NULL)
				tmp = tmp->next;
			tmp->next = new_cmd;
		}
	}
}

int	cmd_lst_size(t_cmd *cmd_lst)
{
	int		count;
	t_cmd	*tmp;

	count = 0;
	tmp = cmd_lst;
	if (!cmd_lst)
		return (0);
	while (tmp->next != NULL)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}
