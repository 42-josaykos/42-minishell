/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_variables_quotes.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 12:26:51 by jonny             #+#    #+#             */
/*   Updated: 2021/06/01 12:58:28 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/msh.h"

void	handle_variables_quotes(char *buf, t_ast **token, t_env *env_lst)
{
	char	tmp[BUF_SIZE];

	ft_bzero(tmp, BUF_SIZE);
	if ((*token)->type == VAR)
	{
		ft_strlcpy(tmp, (*token)->value, ft_strlen((*token)->value) + 1);
		expand_var(buf, tmp, env_lst, token);
		if ((*token) && (*token)->type != VAR)
			ft_strcat(buf, (*token)->value);
	}
	else if ((*token)->type == QUEST)
		expand_exit_code(buf, token);
}
