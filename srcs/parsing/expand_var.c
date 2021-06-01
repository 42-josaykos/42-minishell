/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 13:08:29 by jonny             #+#    #+#             */
/*   Updated: 2021/06/01 13:09:51 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/msh.h"

int	have_whitespaces(char *buf)
{
	int	i;

	i = 0;
	while (buf[i])
	{
		if (ft_isblank(buf[i]))
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strsep_var(char **stringp, const char *delim)
{
	int		i;
	int		j;
	char	*tmp;

	tmp = *stringp;
	i = 0;
	while (tmp[i])
	{
		j = 0;
		while (delim[j])
		{
			if (tmp[i] == delim[j])
			{
				tmp = ft_substr(*stringp, 0, i);
				(*stringp) += i;
				return (tmp);
			}
			j++;
		}
		i++;
	}
	tmp = ft_strdup(*stringp);
	*stringp = NULL;
	return (tmp);
}

int	expand_var2(t_ast **token, char *value)
{
	t_ast	*vars;

	vars = parse_args(value);
	if (!(*token)->right)
	{
		token_lst_remove(token);
		(*token) = vars;
		return (1);
	}
	while (vars->right)
		vars = vars->right;
	token_lst_remove(token);
	vars->right = *token;
	(*token)->left = vars;
	while ((*token)->left)
		*token = (*token)->left;
	return (0);
}

void	expand_var(char *tmp, t_env *env_lst, t_ast **token)
{
	char	*ptr;
	char	*value;

	ptr = ft_strsep_var(&tmp, "/=");
	value = get_env(env_lst, ptr);
	if (ptr)
		free(ptr);
	if (value)
	{
		if (have_whitespaces(value))
			expand_var2(token, value);
		else
		{
			free((*token)->value);
			(*token)->value = ft_strdup(value);
			(*token)->type = ARG;
		}
	}
}
