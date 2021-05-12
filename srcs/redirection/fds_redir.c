/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 11:45:10 by jonny             #+#    #+#             */
/*   Updated: 2021/05/12 11:52:57 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/msh.h"

/*
** Redirect stdout. [cmd] (> [new_fd is output]). (> [new_fd is ouput]) [cmd].
*/

void	redir_append(t_state *st, char **args, enum e_type type)
{
	args++;
	if (type == REDIR)
	{
		st->fdout = open(*args, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
		if (st->fdout == -1)
		{
			error_fd(*args);
			return ;
		}
	}
	else if (type == APPEND)
	{
		st->fdout = open(*args, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
		if (st->fdout == -1)
		{
			error_fd(*args);
			return ;
		}
	}
	dup2(st->fdout, STDOUT);
	ft_close(st->fdout);
}

/*
** arg as input `[cmd] < [input]`
*/

int	input(t_state *st, char **args)
{
	args++;
	st->fdin = open(*args, O_RDONLY, S_IRWXU);
	if (st->fdin == -1)
	{
		ft_putstr_fd("msh: ", STDERR);
		ft_putstr_fd(*args, STDERR);
		ft_putendl_fd(": No such file or directory", STDERR);
		g_sig.exit_status = 1;
		return (1);
	}
	dup2(st->fdin, STDIN);
	ft_close(st->fdin);
	return (0);
}
