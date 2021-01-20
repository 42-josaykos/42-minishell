/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 11:31:49 by jonny             #+#    #+#             */
/*   Updated: 2021/01/20 16:29:40 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/msh.h"

/*
** Returns 0 if the file exists.
*/

int	file_exists(char *filename)
{
	struct stat	buf;

	return (stat(filename, &buf));
}
