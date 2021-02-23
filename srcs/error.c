/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 13:24:33 by jonny             #+#    #+#             */
/*   Updated: 2021/02/23 11:59:58 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/msh.h"

void	error_cases(int errnum, char *cmd, char *arg)
{
	ft_printf("minishell: %s: %s: %s\n", cmd, arg, strerror(errnum));
}

void	error_quotes(void)
{
	ft_putstr_fd("minishell: error: invalid arguments: ", STDERR);
	ft_putstr_fd("opened quotes are not closed\n", STDERR);
}

void	error_cmd(char *cmd)
{
	ft_putstr_fd("minishell: ", STDERR);
	ft_putstr_fd(cmd, STDERR);
	ft_putstr_fd(" : command not found\n", STDERR);
}
