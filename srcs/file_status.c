/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 11:31:49 by jonny             #+#    #+#             */
/*   Updated: 2021/01/21 15:22:50 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/msh.h"

/*
** Returns 0 if the file exists.
*/

int	file_exists(char *filename)
{
	struct stat	buf;

	if (stat(filename, &buf))
		return (0);
	else
		return (1);
}
