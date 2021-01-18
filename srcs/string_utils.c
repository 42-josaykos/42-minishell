/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 13:02:43 by jonny             #+#    #+#             */
/*   Updated: 2021/01/18 17:57:12 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"
#include <ctype.h>

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

int	ft_isblank(int c)
{
	if (c >= 0)
	{
		if (c == ' ' || c == '\t')
			return (1);
		else
			return (0);
	}
	return (0);
}

bool	is_empty(char *str)
{
	bool	ret;

	ret = true;
	while (*str)
	{
		if (ft_isblank(*str))
			str++;
		else
		{
			ret = false;
			break ;
		}
	}
	return (ret);
}
