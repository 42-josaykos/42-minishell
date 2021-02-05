/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 11:47:40 by jonny             #+#    #+#             */
/*   Updated: 2021/02/05 13:51:10 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/msh.h"

int 	exit_msh(int status, char *env, t_env **env_lst, t_cmd **cmd_lst)
{
	free_all(env, env_lst, cmd_lst);
	ft_printf("========> Exit Status: %d\n", status);
	exit(status);
	return (status);
}
