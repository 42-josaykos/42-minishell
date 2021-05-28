/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 11:17:39 by jonny             #+#    #+#             */
/*   Updated: 2021/05/28 18:11:34 by jonny            ###   ########.fr       */
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

void	expand_var(char *buf, char *tmp, t_env *env_lst)
{
	char	*ptr;
	char	*value;

	ptr = NULL;
	ptr = ft_strsep_var(&tmp, "/=");
	value = get_env(env_lst, ptr);
	if (ptr)
		free(ptr);
	if (value)
	{
		ft_strcat(buf, value);
	}
	if (tmp)
		ft_strcat(buf, tmp);
}

void	handle_variables(char *buf, t_ast *token, t_env *env_lst)
{
	char	tmp[BUF_SIZE];
	char	*nbr;

	ft_bzero(tmp, BUF_SIZE);
	if (token->type == VAR)
	{
		ft_strlcpy(tmp, token->value, ft_strlen(token->value) + 1);
		expand_var(buf, tmp, env_lst);
	}
	else if (token->type == QUEST)
	{
		if (g_sig.dollar_quote)
		{
			nbr = ft_itoa(g_sig.exit_status);
			ft_strcat(buf, nbr);
			free(nbr);
		}
		else
			ft_strcat(buf, token->value);
	}
	g_sig.dollar_quote = false;
}
