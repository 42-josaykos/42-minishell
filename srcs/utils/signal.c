/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 14:26:25 by jonny             #+#    #+#             */
/*   Updated: 2021/03/09 11:12:34 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/msh.h"

void	sig_init(void)
{
	g_sig.sigint = 0;
	g_sig.sigquit = 0;
	g_sig.pid = 0;
	g_sig.exit_status = 0;
}

void	sig_int(void)
{
	if (g_sig.pid == 0)
	{
		ft_putstr_fd(GREEN, STDERR);
		ft_putstr_fd("\nminishell ❯ ", STDERR);
		ft_putstr_fd(RESET, STDERR);
		g_sig.exit_status = 1;
	}
	else
	{
		ft_putstr_fd("\n", STDERR);
		g_sig.exit_status = 130;
	}
	g_sig.sigint = 1;
}

void	sig_quit(void)
{
	if (g_sig.pid != 0)
	{
		ft_putstr_fd("Quit\n", STDERR);
		g_sig.exit_status = 131;
		g_sig.sigquit = 1;
	}
	else
		ft_putstr_fd("\b\b  \b\b", STDERR);
}

void	handle_signal(int signal)
{
	if (signal == SIGINT)
		sig_int();
	if (signal == SIGQUIT)
		sig_quit();
}

void	catch_signal(void)
{
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, handle_signal);
}
