/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 12:38:26 by jonny             #+#    #+#             */
/*   Updated: 2021/01/20 12:50:42 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

void	exec_builtin(int ret, t_env *env_lst, t_cmd *cmd_lst)
{
	if (ret == EXPORT)
	{
		export_env(&env_lst, "USER", "testuser");
		ft_printf("env var testkey=testvalue added to the env list.\n");
	}
	else if (ret == CD)
		cd(cmd_lst->args[1], env_lst);
}

int	is_builtin(char *cmd)
{
	if (!ft_strncmp(cmd, "exit", 4))
		return (EXIT);
	else if (!ft_strncmp(cmd, "export", 6))
		return (EXPORT);
	else if (!ft_strncmp(cmd, "cd", 2))
		return (CD);
	return (0);
}
