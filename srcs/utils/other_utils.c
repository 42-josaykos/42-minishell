/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 13:28:04 by jonny             #+#    #+#             */
/*   Updated: 2021/01/31 18:19:53 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/msh.h"

char	**free_2darray(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free((void*)tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

void	handle(int signum)
{
	(void)signum;
	ft_printf("%s%s%s", BOLD_GREEN, "\nminishell $ ", RESET);
}

void	handle_signal(int signum)
{
	signal(signum, handle);
}
