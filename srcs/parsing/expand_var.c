/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 13:08:29 by jonny             #+#    #+#             */
/*   Updated: 2021/06/01 15:22:18 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/msh.h"

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

void	set_arg_types(t_ast **vars)
{
	t_ast	*ptr;

	ptr = *vars;
	while (ptr)
	{
		if (ptr->type != WHITESPACE)
			ptr->type = ARG;
		ptr = ptr->right;
	}
}

int	expand_var2(t_ast **token, char *value)
{
	t_ast	*vars;

	vars = parse_args(value);
	set_arg_types(&vars);
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

void	expand_var3(char *buf, char *tmp, t_ast **token, char *value)
{
	free((*token)->value);
	if (tmp)
	{
		ft_strlcat(buf, value, ft_strlen(value) + 1);
		ft_strcat(buf, tmp);
		(*token)->value = ft_strdup(buf);
	}
	else
		(*token)->value = ft_strdup(value);
	(*token)->type = ARG;
}

void	expand_var(char *tmp, t_env *env_lst, t_ast **token)
{
	char	*ptr;
	char	*value;
	char	buf[BUF_SIZE];

	ft_bzero(buf, BUF_SIZE);
	ptr = ft_strsep_var(&tmp, "/=");
	value = get_env(env_lst, ptr);
	if (ptr)
		free(ptr);
	if (value)
	{
		if (have_whitespaces(value))
			expand_var2(token, value);
		else
			expand_var3(buf, tmp, token, value);
	}
}
