/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 13:02:43 by jonny             #+#    #+#             */
/*   Updated: 2021/02/23 17:17:58 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/msh.h"

/*
** Implementation of strsep
** $ man strsep
*/

char 	*ft_strsep(char **stringp, const char *delim)
{
	int		i;
	int		j;
	char	*tmp;

	tmp = *stringp;
	if (*stringp == NULL)
		return (NULL);
	i = 0;
	while (tmp[i])
	{
		j = 0;
		while (delim[j])
		{
			if (tmp[i] == delim[j])
			{
				tmp[i] = '\0';
				*stringp += (i + 1);
				return (tmp);
			}
			j++;
		}
		i++;
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

int	ft_readline2(char *tmp, char **str)
{
	int		len;

	len = ft_strlen(tmp);
	if (tmp[0] != 0 && tmp[len - 1] == '\n')
	{
		*str = ft_calloc(len + 1, sizeof(char));
		ft_strlcpy(*str, tmp, len + 1);
		return (1);
	}
	return (0);
}

char	*ft_readline(char *prompt)
{
	char	*str;
	char	buf[BUF_SIZE];
	char	tmp[BUF_SIZE];
	int		ret;

	ret = 0;
	str = NULL;
	ft_putstr_fd(prompt, STDERR);
	ft_bzero(tmp, BUF_SIZE);
	while (1)
	{
		ft_bzero(buf, BUF_SIZE);
		ret = read(0, buf, BUF_SIZE);
		if (ret == 0 && !ft_strlen(tmp))
			return (NULL);
		else
		{
			ft_strcat(tmp, buf);
			if (ft_readline2(tmp, &str))
				break ;
		}
	}
	return (str);
}
