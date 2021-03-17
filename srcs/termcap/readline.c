/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 11:04:58 by jonny             #+#    #+#             */
/*   Updated: 2021/03/17 12:02:10 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/msh.h"
#include <stdio.h>
#include <unistd.h>

char	read_key(char c)
{
	if (c == '\e')
		ft_putendl_fd("escape detected !", STDOUT_FILENO);
	return (c);
}

char	*ft_readlinev2(t_state *st, t_env *env_lst, char *prompt)
{
	char	*str;
	char	c;
	char	buf[BUF_SIZE];
	char	key;

	str = NULL;
	print_prompt(prompt, GREEN);
	enable_raw_mode(st, env_lst);
	ft_bzero(buf, BUF_SIZE);
	while (read(STDIN_FILENO, &c, 1) == 1)
	{
		key = read_key(c);
		ft_strlcat(buf, &c, BUF_SIZE);
		if (c == '\n')
			break ;
		if (key != '\e')
			write(STDOUT_FILENO, &c, 1);
		else
			print_prompt(prompt, GREEN);
	}
	write(STDOUT_FILENO, "\n\r", 2);
	str = ft_calloc(ft_strlen(buf), sizeof(char) + 1);
	ft_strlcpy(str, buf, BUF_SIZE);
	return (str);
}
