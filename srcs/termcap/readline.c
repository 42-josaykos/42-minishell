/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 11:04:58 by jonny             #+#    #+#             */
/*   Updated: 2021/03/17 12:33:38 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/msh.h"
#include <stdio.h>
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
		ft_strlcat(buf, &c, BUF_SIZE);
		if (c == '\n')
			break ;
		if (key != '\e')
			write(STDOUT_FILENO, &c, 1);
	}
	if (key == '\n')
		write(STDOUT_FILENO, "\n\r", 2);
	str = ft_calloc(ft_strlen(buf), sizeof(char) + 1);
	ft_strlcpy(str, buf, BUF_SIZE);
	return (str);
}
