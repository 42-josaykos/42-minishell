/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 11:04:58 by jonny             #+#    #+#             */
/*   Updated: 2021/03/23 12:30:12 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/msh.h"

int	read_key(void)
{
	char	c;
	char	seq[2];

	while (read(STDIN_FILENO, &c, 1) != 1)
		;
	if (c == '\e')
	{
		if (read(STDIN_FILENO, &seq[0], 1) != 1)
			return ('\e');
		if (read(STDIN_FILENO, &seq[1], 1) != 1)
			return ('\e');
		if (seq[0] == '[')
		{
			if (seq[1] == 'A')
				return (ARROW_UP);
			if (seq[1] == 'B')
				return (ARROW_DOWN);
		}
	}
	return (c);
}

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

char	*ft_readlinev2(t_state *st, char *prompt)
{
	char	*str;
	char	c;
	int		key;
	int		len;

	str = NULL;
	print_prompt(prompt, GREEN);
	ft_bzero(g_sig.buf, BUF_SIZE);
	while (1)
	{
		key = read_key();
		c = (char)key;
		if (ft_isprint(c) || c == '\n')
		{
			write(STDOUT_FILENO, &c, 1);
			ft_strlcat(g_sig.buf, &c, BUF_SIZE);
		}
		if (key == ARROW_UP)
		{
			if (st->history)
			{
				len = ft_strlen(g_sig.buf);
				if (st->history && st->history->previous && len)
					st->history = st->history->previous;
				while (len > 0)
				{
					ft_putstr_fd("\b \b", STDOUT);
					len--;
				}
				ft_bzero(g_sig.buf, BUF_SIZE);
				ft_strlcpy(g_sig.buf, st->history->value, BUF_SIZE);
				ft_putstr_fd(g_sig.buf, STDOUT);
			}
		}
		if (key == ARROW_DOWN)
		{
			if (st->history && st->history->next)
			{
				st->history = st->history->next;
				len = ft_strlen(g_sig.buf);
				while (len > 0)
				{
					ft_putstr_fd("\b \b", STDOUT);
					len--;
				}
				ft_bzero(g_sig.buf, BUF_SIZE);
				ft_strlcpy(g_sig.buf, st->history->value, BUF_SIZE);
				ft_putstr_fd(g_sig.buf, STDOUT);
			}
		}
		if (key == CTRL_C)
			handle_ctrl_c(prompt);
		if (key == CTRL_D)
			handle_ctrl_d(&c);
		if (key == BACKSPACE)
			handle_backspace();
		if (c == '\n')
			break ;
	}
	str = ft_calloc(ft_strlen(g_sig.buf), sizeof(char) + 1);
	ft_strlcpy(str, g_sig.buf, BUF_SIZE);
	return (str);
}
