/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 15:02:22 by jonny             #+#    #+#             */
/*   Updated: 2021/01/20 15:24:24 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

/*
** Print current directory.
*/

void	print_cwd(void)
{
	char	buf[MAXCHAR];

	getcwd(buf, sizeof(buf));
	ft_printf("%s\n", buf);
}
