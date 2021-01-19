/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 11:31:49 by jonny             #+#    #+#             */
/*   Updated: 2021/01/17 17:07:17 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

/*
** Returns 0 if the file exists.
*/

int	file_exists(char *filename)
{
	struct stat	buf;

	return (stat(filename, &buf));
}
