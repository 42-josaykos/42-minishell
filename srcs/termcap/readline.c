/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 11:04:58 by jonny             #+#    #+#             */
/*   Updated: 2021/03/17 15:31:20 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/msh.h"
#include <stdio.h>
#include <term.h>
#include <unistd.h>

int	read_key(void)
{
	char c;
	char seq[3];

	while (read(STDIN_FILENO, &c, 1) != 1)
	{
		;
	}
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

char	*ft_readlinev2(t_state *st, t_env *env_lst, char *prompt)
{
	char	*str;
	char	c;
	char	buf[BUF_SIZE];
	int		key;

	str = NULL;
	print_prompt(prompt, GREEN);
	enable_raw_mode(st, env_lst);
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
			write(STDOUT_FILENO, "get arrow up !", 14);
			ft_bzero(buf, BUF_SIZE);
		}
		if (key == ARROW_DOWN)
		{
			write(STDOUT_FILENO, "get arrow down !", 16);
			ft_bzero(buf, BUF_SIZE);
		}
		if (key == 127)
		{
			st->termcap = tgetstr("dm", NULL);
			tputs(st->termcap, 1, ft_putchar);
			write(STDOUT_FILENO, &c, 1);
			st->termcap = tgetstr("dc", NULL);
			tputs(st->termcap, 1, ft_putchar);
			st->termcap = tgetstr("ed", NULL);
			tputs(st->termcap, 1, ft_putchar);
		}
		if (c == '\n')
			break ;
	}
	str = ft_calloc(ft_strlen(buf), sizeof(char) + 1);
	ft_strlcpy(str, buf, BUF_SIZE);
	return (str);
}
