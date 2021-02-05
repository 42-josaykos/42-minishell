/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 15:02:22 by jonny             #+#    #+#             */
/*   Updated: 2021/02/05 16:22:24 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/msh.h"

/*
** Print current directory.
*/

void	print_cwd(void)
{
	char	buf[MAXCHAR];

	getcwd(buf, sizeof(buf));
	printf("%s\n", buf);
}
