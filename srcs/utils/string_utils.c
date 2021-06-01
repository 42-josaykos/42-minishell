/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 13:02:43 by jonny             #+#    #+#             */
/*   Updated: 2021/06/01 15:19:55 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/msh.h"

/*
** Implementation of strsep
** $ man strsep
*/

char	*ft_strsep(char **stringp, const char *delim)
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

void	check_buffer_overflow(char *buf, char *tmp)
{
	if (buf[BUF_SIZE - 1] != 0)
	{
		error_syntax(&buf[BUF_SIZE - 1]);
		ft_bzero(buf, BUF_SIZE);
		ft_strlcpy(buf, "\0", BUF_SIZE);
	}
	ft_strlcat(tmp, buf, BUF_SIZE);
}

void	print_prompt(char *prompt, char *color)
{
	ft_putstr_fd(color, STDERR);
	ft_putstr_fd(prompt, STDERR);
	ft_putstr_fd(RESET, STDERR);
}

int	have_whitespaces(char *buf)
{
	int	i;

	i = 0;
	while (buf[i])
	{
		if (ft_isblank(buf[i]))
			return (1);
		i++;
	}
	return (0);
}
