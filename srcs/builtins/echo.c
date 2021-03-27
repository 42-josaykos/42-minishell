/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 12:21:19 by jonny             #+#    #+#             */
/*   Updated: 2021/03/27 15:54:14 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/msh.h"

static void	echo_variable(t_env *env_lst, char *str)
{
	char	*var;

	var = get_env(env_lst, str + 1);
	if (str[1] && var)
		ft_putstr_fd(var, STDIN);
	else
		ft_putstr_fd(str, STDIN);
}

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
		if (*arg[i] == '$')
			echo_variable(env_lst, arg[i]);
		else
			ft_putstr_fd(arg[i], STDIN);
		if (arg[i + 1])
			write(STDIN, " ", 1);
		i++;
	}
	if (!isn)
		write (STDIN, "\n", 1);
	return (0);
}
