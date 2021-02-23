/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 12:32:40 by jonny             #+#    #+#             */
/*   Updated: 2021/02/23 11:46:20 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/msh.h"

bool	check_pipe(char **str)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (str[i][j] == '|')
				return (true);
			j++;
		}
		i++;
	}
	return (false);
}

static void	init_piped_cmd(t_cmd *new_cmd, t_cmd **piped_cmd, char *buffer)
{			
	new_cmd = ft_calloc(1, sizeof(t_cmd));
	new_cmd->args = split_whitespace(buffer);
	new_cmd->next = NULL;
	cmd_lst_add(piped_cmd, new_cmd);
}

void	parse_pipe(char *str, t_cmd **piped_cmd)
{
	int		i;
	int		j;
	int		k;
	char	buffer[BUF_SIZE];
	t_cmd	*new_cmd[BUF_SIZE];

	i = 0;
	j = 0;
	k = 0;
	ft_bzero(buffer, BUF_SIZE);
	while (str[i])
	{
		if (i != 0 && (str[i] == '|' || str[i + 1] == '\0'))
		{
			init_piped_cmd(new_cmd[k], piped_cmd, buffer);
			ft_bzero(buffer, BUF_SIZE);
			i++;
			k++;
			j = 0;
			continue ;
		}
		buffer[j] = str[i];
		i++;
		j++;
	}
}
