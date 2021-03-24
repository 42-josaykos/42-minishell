/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 12:38:53 by jonny             #+#    #+#             */
/*   Updated: 2021/03/24 12:41:38 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/msh.h"

void	handle_ctrl_c(char *prompt)
{
	write(STDOUT_FILENO, "\n\r", 2);
	print_prompt(prompt, GREEN);
	ft_bzero(g_sig.buf, BUF_SIZE);
}

void	handle_ctrl_d(char *c)
{
	if (g_sig.buf[0] == '\0')
	{
		ft_strlcpy(g_sig.buf, "exit\n", 6);
		*c = '\n';
	}
}

void	handle_backspace(void)
{
	int	len;

	len = ft_strlen(g_sig.buf);
	if (len && g_sig.buf[len - 1])
		ft_putstr_fd("\b \b", STDOUT);
	g_sig.buf[ft_strlen(g_sig.buf) - 1] = '\0';
}

void	handle_arrow_up(t_hist **history)
{
	int	len;

	len = 0;
	if (*history)
	{
		len = ft_strlen(g_sig.buf);
		if (*history && (*history)->previous && len)
			*history = (*history)->previous;
		clear_buf();
		ft_strlcpy(g_sig.buf, (*history)->value, BUF_SIZE);
		ft_putstr_fd(g_sig.buf, STDOUT);
	}
}

void	handle_arrow_down(t_hist **history)
{
	int	len;

	len = 0;
	if (*history && (*history)->next)
	{
		*history = (*history)->next;
		clear_buf();
		ft_strlcpy(g_sig.buf, (*history)->value, BUF_SIZE);
		ft_putstr_fd(g_sig.buf, STDOUT);
	}
	else if (g_sig.buf[0] != '\0')
		clear_buf();
}
