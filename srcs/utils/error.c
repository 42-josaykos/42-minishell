/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 13:24:33 by jonny             #+#    #+#             */
/*   Updated: 2021/05/26 13:48:11 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/msh.h"

void	error_cases(int errnum, char *cmd, char *arg)
{
	if (*cmd == '.')
		g_sig.exit_status = 2;
	else
		g_sig.exit_status = 1;
	ft_putstr_fd("msh: ", STDERR);
	ft_putstr_fd(cmd, STDERR);
	ft_putstr_fd(": ", STDERR);
	ft_putstr_fd(arg, STDERR);
	ft_putstr_fd(": ", STDERR);
	ft_putstr_fd(strerror(errnum), STDERR);
	ft_putstr_fd("\n", STDERR);
}

void	error_quotes(void)
{
	ft_putstr_fd("msh: error: invalid arguments: ", STDERR);
	ft_putstr_fd("opened quotes are not closed\n", STDERR);
}

void	error_cmd(char *cmd)
{
	g_sig.exit_status = 127;
	ft_putstr_fd("msh: ", STDERR);
	ft_putstr_fd(cmd, STDERR);
	ft_putstr_fd(" : command not found\n", STDERR);
}

int	error_syntax(char *cmd)
{
	g_sig.exit_status = 2;
	ft_putstr_fd("msh: error syntax near unexpected token ", STDERR);
	ft_putstr_fd("`", STDERR);
	ft_putstr_fd(cmd, STDERR);
	ft_putstr_fd("'\n", STDERR);
	return (1);
}

void	error_fd(char *arg)
{
	ft_putstr_fd("msh: ", STDERR);
	ft_putstr_fd(arg, STDERR);
	ft_putendl_fd(": No such file or directory", STDERR);
	g_sig.exit_status = 1;
	return ;
}
