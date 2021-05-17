/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 15:04:59 by jonny             #+#    #+#             */
/*   Updated: 2021/05/17 12:38:01 by jonny            ###   ########.fr       */
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

void	print_export_variables2(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		ft_putstr_fd("declare -x ", STDOUT);
		ft_putendl_fd(strs[i], STDOUT_FILENO);
		i++;
	}
	free_2darray(strs);
}

static void	concat_key_value(char *buf, t_env *env_lst)
{
	ft_strlcat(buf, "=", BUF_SIZE);
	ft_strlcat(buf, "\"", BUF_SIZE);
	ft_strlcat(buf, env_lst->value, BUF_SIZE);
	ft_strlcat(buf, "\"", BUF_SIZE);
}

void	print_export_variables(t_env *env_lst)
{
	char	**strs;
	char	buf[BUF_SIZE];
	int		len;
	int		i;

	ft_bzero(buf, BUF_SIZE);
	len = env_lst_size(env_lst);
	strs = ft_calloc(len + 1, sizeof(char *));
	i = 0;
	while (env_lst)
	{
		ft_strlcat(buf, env_lst->key, BUF_SIZE);
		if (env_lst->value)
			concat_key_value(buf, env_lst);
		strs[i] = ft_strdup(buf);
		i++;
		ft_bzero(buf, BUF_SIZE);
		env_lst = env_lst->next;
	}
	alpha_sort(strs, len);
	print_export_variables2(strs);
}
