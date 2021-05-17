/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 11:04:58 by jonny             #+#    #+#             */
/*   Updated: 2021/05/17 12:43:57 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/msh.h"

int	read_key(void)
{
	char	c;
	char	seq[2];
	char	seq2[3];

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
			else if (read(STDIN_FILENO, seq2, 3) != 1)
				return ('\e');
		}
	}
	return (c);
}

void	clear_buf(void)
{
	int	len;

	len = ft_strlen(g_sig.buf);
	while (len > 0)
	{
		ft_putstr_fd("\b \b", STDOUT);
		len--;
	}
	ft_bzero(g_sig.buf, BUF_SIZE);
}

void	handle_keys(int key, t_state *st, char *prompt, char *c)
{
	if (key == ARROW_UP)
		handle_arrow_up(&st->history);
	if (key == ARROW_DOWN)
		handle_arrow_down(&st->history);
	if (key == CTRL_C)
		handle_ctrl_c(prompt);
	if (key == CTRL_D)
		handle_ctrl_d(c);
	if (key == BACKSPACE)
		handle_backspace();
}

char	*ft_readlinev2(t_state *st, char *prompt)
{
	char	*str;
	char	c;
	int		key;

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
		handle_keys(key, st, prompt, &c);
		if (c == '\n')
			break ;
	}
	str = ft_calloc(ft_strlen(g_sig.buf), sizeof(char) + 1);
	ft_strlcpy(str, g_sig.buf, BUF_SIZE);
	return (str);
}
