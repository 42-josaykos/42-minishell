/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 11:17:39 by jonny             #+#    #+#             */
/*   Updated: 2021/05/28 12:19:04 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/msh.h"

void	expand_var(char *buf, char *tmp, t_env *env_lst)
{
	char	*ptr;
	char	*value;

	ptr = ft_strsep(&tmp, "/");
	value = get_env(env_lst, ptr);
	if (value)
	{
		ft_strcat(buf, value);
	}
	if (tmp)
	{
		ft_strcat(buf, "/");
		ft_strcat(buf, tmp);
	}
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
