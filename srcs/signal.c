/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 14:26:25 by jonny             #+#    #+#             */
/*   Updated: 2021/02/02 15:44:28 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/msh.h"

bool	g_interrupt = 0;

void	handle_signal(int signal)
{
	if (signal == SIGINT)
	{
		ft_printf("%s%s%s", BOLD_GREEN, "\nminishell $ ", RESET);
		g_interrupt = 1;
	}
	if (signal == SIGQUIT)
	{
		ft_printf("%s%s%s", BOLD_GREEN, "\nminishell $ ", RESET);
		g_interrupt = 1;
	}
}

void	catch_signal(void)
{
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, handle_signal);
}
