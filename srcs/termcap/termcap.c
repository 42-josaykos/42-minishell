/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 10:54:48 by jonny             #+#    #+#             */
/*   Updated: 2021/03/16 11:37:13 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/msh.h"

void	init_termcap(t_state *st, t_env *env_lst)
{
	export_env(&env_lst, "TERM", "xterm-256color");
	st->term_type = get_env(env_lst, "TERM");
	tgetent(NULL, st->term_type);
	ft_bzero(&st->termios_new, sizeof(struct termios));
	tcgetattr(STDIN_FILENO, &st->termios_backup);
	st->termios_new = st->termios_backup;
	st->termios_new.c_lflag &= ~(ICANON);
	st->termios_new.c_lflag &= ~(ECHO);
	st->termios_new.c_cc[VMIN] = 1;
	st->termios_new.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &st->termios_new);
	return ;
}
