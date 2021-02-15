/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 12:32:40 by jonny             #+#    #+#             */
/*   Updated: 2021/02/15 15:36:15 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/msh.h"

void	parse_pipe(char *str, t_cmd **piped_cmd)
{
	int	i;
	int j;
	char buffer[BUF_SIZE];
	t_cmd *new_cmd;

	i = 0;
	j = 0;
	ft_bzero(buffer, BUF_SIZE);
	while (str[i])
	{
		if (str[i] == '|')
		{
			new_cmd = ft_calloc(1, sizeof(t_cmd));
			new_cmd->args = split_whitespace(buffer);
			new_cmd->next = NULL;
			cmd_lst_add(piped_cmd, new_cmd);
			ft_bzero(buffer, BUF_SIZE);
		}
		buffer[j] = str[i];
		i++;
		j++;
	}
}

// int	check_pipe(char *input, t_cmd *cmd_lst)
// {
// 	char	*tmp[BUF_SIZE];
// 	t_cmd	*new_cmd;
// 	int		i;

// 	new_cmd = NULL;
// 	if (parse_pipe(input, tmp) == true)
// 	{
// 		i = 0;
// 		while (tmp[i])
// 		{
// 			// parse_args(tmp[i], cmd_lst);
// 			new_cmd = ft_calloc(1, sizeof(t_cmd));
// 			new_cmd->next = NULL;
// 			cmd_lst_add(&cmd_lst, new_cmd);
// 			cmd_lst = cmd_lst->next;
// 			i++;
// 		}
// 		return (1);
// 	}
// 	return (0);
// }
