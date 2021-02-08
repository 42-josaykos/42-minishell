/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 13:02:43 by jonny             #+#    #+#             */
/*   Updated: 2021/01/30 13:36:31 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/msh.h"

/*
** Implementation of strsep
** $ man strsep
*/

int		check_dquotes(char *input)
{
	int	i;
	int	ret;

	i = 0;
	ret = 1;
	while (input[i])
	{
		if (input[i] == '\"')
			ret *= -1;
		i++;
	}
	return (ret)
;}

char	*dquotes_loop(char *str, int *i, char **stringp)
{
	*i += 1;
	while (str[*i] && str[*i] != str[0])
		*i += 1;
		str[*i] = 0;
		*stringp += (*i + 1);
	return (str); 
}

char 	*ft_strsep2(char **stringp)
{
	int		i;
	char	*tmp;

	tmp = *stringp;
	if (*stringp == NULL)
		return (NULL);
	i = 0;
	while (tmp[i])
	{
		if ((tmp[i] == '\"' || tmp[i] == '\'') && i == 0)
			return (dquotes_loop(tmp, &i, stringp));
		else if (tmp[i] == ' ' || tmp[i] == '\t')
		{
			tmp[i] = '\0';
			if (tmp[i] != '\"' && tmp[i] != '\'')
				i++;
			*stringp += i;
			return (tmp);
		}
		i++;
	}
	*stringp = NULL;
	return (tmp);
}
