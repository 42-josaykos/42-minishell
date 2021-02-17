/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multi_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 15:21:45 by jonny             #+#    #+#             */
/*   Updated: 2021/02/17 11:19:08 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/msh.h"

void 	has_piped_cmd(t_state *status, t_env *env_lst, char **args)
{
	int		i;
	char	buffer[BUF_SIZE];
	t_cmd	*piped_cmd;
	t_cmd	*ptr;
	int		len;

	i = 0;
	piped_cmd = NULL;
	len = 0;
	ft_bzero(buffer, BUF_SIZE);
	while (args[i])
	{
		ft_strcat(buffer, args[i]);
		ft_strcat(buffer, " ");
		i++;
	}
	parse_pipe(buffer, &piped_cmd);
	len = cmd_lst_size(piped_cmd);
	ptr = piped_cmd;
	while (ptr)
	{
		filepath_exists(env_lst, ptr);
		ptr = ptr->next;
	}
	fork_pipes(status, len, piped_cmd);
	clear_previous_cmd(piped_cmd, status);
	free(piped_cmd);
}
