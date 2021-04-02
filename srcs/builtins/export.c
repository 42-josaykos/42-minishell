/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 15:04:59 by jonny             #+#    #+#             */
/*   Updated: 2021/04/02 11:27:06 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/msh.h"

static void	content_add(t_env *node, char *key, char *value)
{
	if (key)
		node->key = key;
	if (value)
		node->value = value;
}

/*
** Create a new env variable (key=value) and add it to the env list.
*/

void	*export_env(t_env **env_lst, char *key, char *value)
{
	t_env	*new_env;
	t_env	*tmp;

	tmp = *env_lst;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, key, ft_strlen(key) + 1))
		{
			free(tmp->key);
			free(tmp->value);
			content_add(tmp, key, value);
			return (tmp);
		}
		tmp = (tmp)->next;
	}
	new_env = ft_calloc(1, sizeof(t_env));
	if (!new_env)
		return (NULL);
	new_env->next = NULL;
	content_add(new_env, key, value);
	env_lst_add(env_lst, new_env);
	return (new_env);
}

void	alpha_sort(char **strs, int len)
{
	int i;
	int j;
	char tmp[BUF_SIZE];

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

void	print_export_variables2(char **strs)
{
	int i;
	i = 0;
	while (strs[i])
	{
		ft_putstr_fd("declare -x ", STDOUT);
		ft_putendl_fd(strs[i], STDOUT_FILENO);
		i++;
	}
	free_2darray(strs);

}

void	print_export_variables(t_env *env_lst)
{
	char	**strs;
	char	buf[BUF_SIZE];
	t_env	*ptr;
	int len;
	int i;

	ft_bzero(buf, BUF_SIZE);
	ptr = env_lst;
	len = 0;
	while (ptr)
	{
		len++;
		ptr = ptr->next;
	}
	strs = ft_calloc(len + 1, sizeof(char *));
	i = 0;
	while (env_lst)
	{
		ft_strlcat(buf, env_lst->key, BUF_SIZE);
		if (env_lst->value)
		{
			ft_strlcat(buf, "=", BUF_SIZE);
			ft_strlcat(buf, "\"", BUF_SIZE);
			ft_strlcat(buf, env_lst->value, BUF_SIZE);
			ft_strlcat(buf, "\"", BUF_SIZE);
		}
		strs[i] = ft_strdup(buf);
		i++;
		ft_bzero(buf, BUF_SIZE);
		env_lst = env_lst->next;
	}
	alpha_sort(strs, len);
	print_export_variables2(strs);
}
