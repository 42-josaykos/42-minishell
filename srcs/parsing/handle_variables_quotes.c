/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_variables_quotes.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 12:26:51 by jonny             #+#    #+#             */
/*   Updated: 2021/05/31 22:29:18 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/msh.h"

void	handle_variables_quotes(char *buf, t_ast **token, t_env *env_lst)
{
	char	tmp[BUF_SIZE];
	char	*nbr;

	ft_bzero(tmp, BUF_SIZE);
	if ((*token)->type == VAR)
	{
		ft_strlcpy(tmp, (*token)->value, ft_strlen((*token)->value) + 1);
		expand_var(buf, tmp, env_lst, token);
		ft_strcat(buf, (*token)->value);
	}
	else if ((*token)->type == QUEST)
	{
		if (g_sig.dollar_quote)
		{
			nbr = ft_itoa(g_sig.exit_status);
			ft_strcat(buf, nbr);
			free(nbr);
		}
		else
			ft_strcat(buf, (*token)->value);
	}
	g_sig.dollar_quote = false;
}
