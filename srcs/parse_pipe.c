/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <jonny@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 12:32:40 by jonny             #+#    #+#             */
/*   Updated: 2021/01/15 12:49:30 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

bool	parse_pipe(char *str, char **piped)
{
	int	i;

	i = 0;
	while (i < 100)
	{
		piped[i] = ft_strsep(&str, "|");
		if (piped[i] == NULL)
			break ;
		i++;
	}
	if (piped[1] == NULL)
		return (false);
	return (true);
}

void	check_pipe(char *input, char **args, char **piped)
{
	char	*tmp[100];
	int		i;

	i = 1;
	if (parse_pipe(input, tmp) == true)
	{
		parse_args(tmp[0], args);
		while (tmp[i] != NULL)
		{
			parse_args(tmp[i], piped);
			i++;
		}
	}
	else
		parse_args(input, args);
}
