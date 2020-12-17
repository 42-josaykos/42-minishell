/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <jonny@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 12:41:57 by jonny             #+#    #+#             */
/*   Updated: 2020/12/17 13:41:45 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

void split_path(t_env *env_lst, char *str)
{
	char	**sub_strs;
	int		i;
    (void)env_lst;

	i = 0;
	sub_strs = ft_split(str, ':');
	ft_printf("str = %s\n", str);
	while (sub_strs[i] != NULL)
    {
        export_env(&env_lst, "path", sub_strs[i]);
		free(sub_strs[i]);
        i++;
    }
	free(sub_strs);
}

void parse_path(t_env *env_lst)
{
    t_env *tmp;

    tmp = env_lst;
    while(tmp)
    {
        if (ft_strncmp(tmp->key, "PATH", 4) == 0)
            split_path(env_lst, tmp->value);
        tmp = tmp->next;
    }
}