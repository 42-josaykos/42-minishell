/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 12:21:19 by jonny             #+#    #+#             */
/*   Updated: 2021/03/23 15:27:41 by jonny            ###   ########.fr       */
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
		ft_printf("%s", arg[i]);
		if (arg[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (!isn)
		write (1, "\n", 1);
	return (0);
}
