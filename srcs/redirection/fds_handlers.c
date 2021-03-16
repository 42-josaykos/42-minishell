/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds_handlers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 11:08:26 by jonny             #+#    #+#             */
/*   Updated: 2021/03/09 15:03:23 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/msh.h"

void	init_fds(t_state **st)
{
	(*st)->fdin = -1;
	(*st)->fdout = -1;
}

void	ft_close(int fd)
{
	if (fd > 0)
		close(fd);
}

void	reset_std(t_state *st)
{
	dup2(st->in, STDIN);
	dup2(st->out, STDOUT);
}

void	close_fds(t_state *st)
{
	ft_close(st->fdin);
	ft_close(st->fdout);
}
