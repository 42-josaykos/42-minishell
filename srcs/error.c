/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 13:24:33 by jonny             #+#    #+#             */
/*   Updated: 2021/02/17 11:21:53 by jonny            ###   ########.fr       */
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
