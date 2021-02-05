/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 11:47:40 by jonny             #+#    #+#             */
/*   Updated: 2021/02/05 16:27:11 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/msh.h"

int 	exit_msh(t_state *status, t_env **env_lst, t_cmd **cmd_lst)
{
	int	code;

	code = status->code;
	free_all(status, env_lst, cmd_lst);
	printf("========> Exit Status: %d\n", code);
	exit(code);
	return (code);
}
