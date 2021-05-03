/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 12:21:19 by jonny             #+#    #+#             */
/*   Updated: 2021/05/03 18:17:42 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/msh.h"

int	builtin_echo(char **arg, t_env *env_lst, int fd)
{
	int		i;
	int		isn;

	(void)fd;
	(void)env_lst;
	isn = 0;
	i = 1;
	if (arg[i] && !ft_strncmp(arg[i], "-n", 3))
		isn = 1;
	i += isn;
	while (arg[i])
	{
		if (*arg[i] != '\0')
			ft_putstr_fd(arg[i], STDOUT);
		if (arg[i + 1])
			write(STDOUT, " ", 1);
		i++;
	}
	if (!isn)
		write (STDOUT, "\n", 1);
	return (0);
}
