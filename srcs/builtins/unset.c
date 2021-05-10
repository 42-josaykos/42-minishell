/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 10:13:30 by jonny             #+#    #+#             */
/*   Updated: 2021/05/10 11:34:35 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/msh.h"

void	builtin_unset(char **variables, t_env **env_lst)
{
	int	i;

	i = 1;
	while (variables[i])
	{
		env_lst_remove(*env_lst, variables[i]);
		i++;
	}
}
