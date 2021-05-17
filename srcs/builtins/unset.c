/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 10:13:30 by jonny             #+#    #+#             */
/*   Updated: 2021/05/17 12:38:22 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/msh.h"

void	builtin_unset(char **variables, t_env **env_lst)
{
	int		i;
	t_env	*tmp;

	i = 1;
	while (variables[i])
	{
		if (!ft_strncmp((*env_lst)->key, variables[i],
				ft_strlen(variables[i]) + 1))
		{
			tmp = (*env_lst)->next;
			if ((*env_lst)->key)
				free((*env_lst)->key);
			if ((*env_lst)->value)
				free((*env_lst)->value);
			free(*env_lst);
			*env_lst = tmp;
		}
		else
			env_lst_remove(*env_lst, variables[i]);
		i++;
	}
}
