/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <jonny@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 15:02:22 by jonny             #+#    #+#             */
/*   Updated: 2020/12/10 16:20:03 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

/*
** Print current directory.
*/

static void	print_cwd(void)
{
	char buf[1024];

	getcwd(buf, sizeof(buf));
	ft_printf("%s\n", buf);
}

int			main(void)
{
	print_cwd();
	return (EXIT_SUCCESS);
}
