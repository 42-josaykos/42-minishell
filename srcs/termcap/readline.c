/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 11:04:58 by jonny             #+#    #+#             */
/*   Updated: 2021/03/18 11:39:02 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/msh.h"
#include <curses.h>
#include <stdio.h>
#include <term.h>
#include <unistd.h>

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

char	*ft_readlinev2(t_state *st, char *prompt)
{
	char	*str;
	char	c;
	char	buf[BUF_SIZE];
	int		key;
	int		len;
	t_hist	*ptr = st->history;

	str = NULL;
	print_prompt(prompt, GREEN);
	ft_bzero(buf, BUF_SIZE);
	while (1)
	{
		key = read_key();
		c = (char)key;
		if (ft_isprint(c) || c == '\n')
		{
			write(STDOUT_FILENO, &c, 1);
			ft_strlcat(buf, &c, BUF_SIZE);
		}
		if (key == ARROW_UP)
		{
			if (ptr && ptr->previous)
			{
				ptr = ptr->previous;
				len = ft_strlen(buf);
				while (len > 0)
				{
					ft_putstr_fd("\b \b", STDOUT);
					len--;
				}
				ft_bzero(buf, BUF_SIZE);
				ft_strlcpy(buf, ptr->value, BUF_SIZE);
				ft_putstr_fd(buf, STDOUT);
			}
		}
		if (key == ARROW_DOWN)
		{
			if (ptr && ptr->next)
			{
				ptr = ptr->next;
				len = ft_strlen(buf);
				while (len > 0)
				{
					ft_putstr_fd("\b \b", STDOUT);
					len--;
				}
				ft_bzero(buf, BUF_SIZE);
				ft_strlcpy(buf, ptr->value, BUF_SIZE);
				ft_putstr_fd(buf, STDOUT);
			}
		}
		if (key == CTRL_C)
		{
			write(STDOUT_FILENO, "\n\r", 2);
			print_prompt(prompt, GREEN);
			ft_bzero(buf, BUF_SIZE);
		}
		if (key == CTRL_D)
		{
			if (buf[0] == '\0')
			{
				ft_strlcpy(buf, "exit\n", 6);
				c = '\n';
			}
		}
		if (key == BACKSPACE)
		{
			ft_putstr_fd("\b \b", STDOUT);
			buf[ft_strlen(buf) - 1] = '\0';
		}
		if (c == '\n')
			break ;
	}
	str = ft_calloc(ft_strlen(buf), sizeof(char) + 1);
	ft_strlcpy(str, buf, BUF_SIZE);
	return (str);
}
