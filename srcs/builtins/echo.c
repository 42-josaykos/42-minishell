/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 12:21:19 by jonny             #+#    #+#             */
/*   Updated: 2021/02/09 16:08:37 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/msh.h"

// void	echo_loop(char *arg, t_env *env_lst, int fd)
// {
// 	char	*str;

// 	// if (arg[0] == '\"')
// 	// 	arg++;
// 	if ((arg[0] != '$') || ((arg[0] == '$') && (ft_strlen(arg) == 1)))
// 		ft_putstr_fd(arg, fd);
// 	else if (arg)
// 	{
// 		arg++;
// 		str = get_env(env_lst, arg);
// 		ft_putstr_fd(str, fd);
// 	}
// }

int	echo(char **arg, t_env *env_lst, int fd)
{
	int		i;
	int		isn;
 
	(void)env_lst;
	isn = 0;
	i = 2;
	if (arg[i] && !ft_strncmp(arg[i], "-n", 3))
		isn = 1;
	i += 2 * isn;
	while (arg[i])
	{
		ft_printf("%s", arg[i]);
		// if (i > (isn + 1))
		// 	write (fd, " ", 1);
		// echo_loop(arg[i], env_lst, fd);
		i++;
	}
	if (!isn)
		write (fd, "\n", 1);
	return (0);
}
