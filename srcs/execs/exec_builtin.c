/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 12:38:26 by jonny             #+#    #+#             */
/*   Updated: 2021/01/20 16:30:45 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/msh.h"

void	exec_builtin(int ret, t_env *env_lst, t_cmd *cmd_lst)
{
	if (ret == EXPORT)
		assign_env(cmd_lst->args[1], &env_lst);
	else if (ret == CD)
		cd(cmd_lst->args[1], env_lst);
	else if (ret == PWD)
		print_cwd();
}

int	is_builtin(char *cmd)
{
	if (!ft_strncmp(cmd, "exit", 4))
		return (EXIT);
	else if (!ft_strncmp(cmd, "export", 6))
		return (EXPORT);
	else if (!ft_strncmp(cmd, "cd", 2))
		return (CD);
	else if (!ft_strncmp(cmd, "pwd", 3))
		return (PWD);
	return (0);
}
