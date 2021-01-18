/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <jonny@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 13:02:43 by jonny             #+#    #+#             */
/*   Updated: 2021/01/15 12:49:38 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

/*
** Implementation of strsep
** $ man strsep
*/

char 	*ft_strsep(char **stringp, const char *delim)
{
	int		i;
	char	*tmp;

	tmp = *stringp;
	if (*stringp == NULL)
		return (NULL);
	while (*delim)
	{
		i = 0;
		while (tmp[i])
		{
			if (tmp[i] == *delim)
			{
				tmp[i] = '\0';
				*stringp += (i + 1);
				return (tmp);
			}
			i++;
		}
		delim++;
	}
	*stringp = NULL;
	return (tmp);
}
