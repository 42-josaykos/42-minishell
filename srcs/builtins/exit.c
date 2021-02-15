/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 11:47:40 by jonny             #+#    #+#             */
/*   Updated: 2021/02/06 15:16:51 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/msh.h"

bool	ft_isnum(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (false);
		str++;
	}
	return (true);
}

int 	exit_msh(t_state *status, t_env **env_lst, t_cmd **cmd_lst)
{
	int	code;

	code = 0;
	ft_putstr_fd("exit\n", STDERR);
	if ((*cmd_lst)->args[1] && !ft_isnum((*cmd_lst)->args[1]))
	{
		code = 255;
		ft_putstr_fd("minishell: exit: ", STDERR);
		ft_putstr_fd((*cmd_lst)->args[1], STDERR);
		ft_putendl_fd(": numeric argument required", STDERR);
	}
	else if ((*cmd_lst)->args[1] && (*cmd_lst)->args[2])
	{
		code = 1;
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR);
	}
	else if ((*cmd_lst)->args[1])
		code = ft_atoi((*cmd_lst)->args[1]);
	free_all(status, env_lst, cmd_lst);
	
	printf("========> Exit Status: %d\n", code);
	exit(code);
	return (code);
}
