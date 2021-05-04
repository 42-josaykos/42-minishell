/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 16:43:39 by jonny             #+#    #+#             */
/*   Updated: 2021/05/04 17:05:39 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/msh.h"

pid_t	create_fork(pid_t *pid)
{
	*pid = fork();
	if (*pid < 0)
		ft_printf("Cannot execute child process.\n");
	return (*pid);
}
