/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 14:07:50 by jonny             #+#    #+#             */
/*   Updated: 2021/03/22 13:58:51 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/msh.h"

void	print_env_lst(t_env *env_lst)
{
	char	env[BUF_SIZE];

	ft_bzero(env, BUF_SIZE);
	while (env_lst)
	{
		if (env_lst->value)
		{
			ft_strlcat(env, env_lst->key, BUF_SIZE);
			ft_strlcat(env, "=", BUF_SIZE);
			ft_strlcat(env, env_lst->value, BUF_SIZE);
			ft_putendl_fd(env, STDOUT);
			ft_bzero(env, BUF_SIZE);
		}
		env_lst = env_lst->next;
	}
}
