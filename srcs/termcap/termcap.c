/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 10:54:48 by jonny             #+#    #+#             */
/*   Updated: 2021/03/17 17:42:22 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/msh.h"

/*
** Enable terminal raw mode
** TODO: term.c_lflag &= ~(ICANON | ECHO);
*/

void	enable_raw_mode(t_state *st)
{
	ft_bzero(&st->termios_new, sizeof(struct termios));
	tcgetattr(STDIN_FILENO, &st->termios_backup);
	st->termios_new = st->termios_backup;
	st->termios_new.c_lflag &= ~(ICANON | ECHO);
	st->termios_new.c_cc[VMIN] = 1;
	st->termios_new.c_cc[VTIME] = 0;
	st->raw_mode = true;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &st->termios_new);
	return ;
}

/*
** Disable terminal raw mode at exit in exit_msh()
*/

void	disable_raw_mode(t_state *st)
{
	if (st->raw_mode)
		tcsetattr(STDIN_FILENO, TCSAFLUSH, &st->termios_backup);
}
