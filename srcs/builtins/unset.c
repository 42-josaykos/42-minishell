/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpascal <alpascal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 10:13:30 by jonny             #+#    #+#             */
/*   Updated: 2021/03/22 14:18:49 by alpascal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/msh.h"

int	unset_env(t_env **env_lst, char *key)
{
	t_env	*tmp;

	tmp = *env_lst;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, key, ft_strlen(key) + 1))
		{
			env_lst_remove(*env_lst, key);
			return (EXIT_SUCCESS);
		}
		tmp = (tmp)->next;
	}
	return (EXIT_SUCCESS);
}

int	builtin_unset(char *str, t_env **env_lst)
{
	int		i;
	char	*env[2];

	i = 0;
	while (i < 2)
	{
		env[i] = ft_strsep(&str, "=");
		if (env[i] == NULL)
			break ;
		if (strlen(env[i]) == 0)
			i--;
		i++;
	}
	return (unset_env(env_lst, env[0]));
}
