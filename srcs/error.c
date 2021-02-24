/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 13:24:33 by jonny             #+#    #+#             */
/*   Updated: 2021/02/24 14:06:13 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/msh.h"
#include <unistd.h>

void	error_cases(int errnum, char *cmd, char *arg)
{
	g_sig.exit_status = 1;
	ft_putstr_fd("msh: ", STDERR);
	ft_putstr_fd(cmd, STDERR);
	write(STDERR, ": ", 2);
	ft_putstr_fd(arg, STDERR);
	write(STDERR, ": ", 2);
	ft_putstr_fd(strerror(errnum), STDERR);
	write(STDERR, "\n", 1);
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
