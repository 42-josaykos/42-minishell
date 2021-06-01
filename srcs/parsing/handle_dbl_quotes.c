/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dbl_quotes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 13:33:32 by jonny             #+#    #+#             */
/*   Updated: 2021/06/01 16:04:48 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/msh.h"

void	handle_dbl_quotes(t_ast **token, char *buf, t_env *env_lst)
{
	if ((*token)->type == VAR
		|| (g_sig.dollar_quote && (*token)->type == QUEST))
		handle_variables_quotes(buf, token, env_lst);
	else if ((*token)->type == ESCAPE && (*token)->right
		&& ((*token)->right->value[0] == '\''
			|| (*token)->right->value[0] == ' '))
		ft_strcat(buf, (*token)->value);
	else if ((*token)->type != DOLLAR
		&& (g_sig.dollar_quote || (*token)->type != ESCAPE)
		&& (*token)->type != DBLQUOTE)
		ft_strcat(buf, (*token)->value);
}
