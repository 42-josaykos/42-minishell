/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_env_lst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 11:41:13 by jonny             #+#    #+#             */
/*   Updated: 2021/05/17 12:38:33 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/msh.h"

void	alpha_sort(char **strs, int len)
{
	int		i;
	int		j;
	char	tmp[BUF_SIZE];

	i = 0;
	ft_bzero(tmp, BUF_SIZE);
	while (i < len)
	{
		j = i + 1;
		while (j < len)
		{
			if (ft_strncmp(strs[i], strs[j], BUF_SIZE) > 0)
			{
				ft_strlcpy(tmp, strs[i], ft_strlen(strs[i]) + 1);
				free(strs[i]);
				strs[i] = ft_strdup(strs[j]);
				free(strs[j]);
				strs[j] = ft_strdup(tmp);
				ft_bzero(tmp, BUF_SIZE);
			}
			j++;
		}
		i++;
	}
}

int	env_lst_size(t_env *env_lst)
{
	int	len;

	len = 0;
	while (env_lst)
	{
		len++;
		env_lst = env_lst->next;
	}
	return (len);
}
