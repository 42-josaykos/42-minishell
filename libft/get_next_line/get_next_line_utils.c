/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <jonny@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 12:07:07 by josaykos          #+#    #+#             */
/*   Updated: 2021/01/05 17:14:06 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	del(char **str)
{
	if (str != NULL)
	{
		free(*str);
		*str = NULL;
	}
}

int 	init_gnl(char **s, int fd, char **line)
{
	if (*s == 0)
		*s = ft_strdup("");
	if (fd < 0 || !line || BUFFER_SIZE <= 0 || !s)
		return (-1);
	return (0);
}
