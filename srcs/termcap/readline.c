/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 11:04:58 by jonny             #+#    #+#             */
/*   Updated: 2021/03/17 11:29:56 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/msh.h"
#include <ctype.h>

char	*ft_readlinev2(t_state *st, t_env *env_lst, char *prompt)
{
	char	*str;
	char	c;
	char	buf[BUF_SIZE];

	str = NULL;
	print_prompt(prompt, GREEN);
	enable_raw_mode(st, env_lst);
	ft_bzero(buf, BUF_SIZE);
	while (read(STDIN_FILENO, &c, 1) == 1)
	{
		ft_strlcat(buf, &c, BUF_SIZE);
		if (c == '\n')
			break ;
	}
	str = ft_calloc(ft_strlen(buf), sizeof(char) + 1);
	ft_strlcpy(str, buf, BUF_SIZE);
	return (str);
}
