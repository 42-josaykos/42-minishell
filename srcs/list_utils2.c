#include "msh.h"

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