/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 11:31:49 by jonny             #+#    #+#             */
/*   Updated: 2021/03/09 11:12:30 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/msh.h"

/*
** Returns 0 if the file exists.
*/

int	file_exists(char *filename)
{
	struct stat	buf;

	if (!filename)
		return (0);
	if (stat(filename, &buf))
		return (0);
	else
		return (1);
}
