/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 17:38:04 by jonny             #+#    #+#             */
/*   Updated: 2021/03/26 17:54:26 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/msh.h"


void 	handle_quotes2(t_ast **token, char *buf, bool dollar_sign)
{
	char *ptr = NULL;
	char c;


	if ((*token)->type == ESCAPE && (*token)->right && dollar_sign)
	{
		c = (*token)->right->value[0];
		ft_strcat(buf, "\n");
		*token = (*token)->right;
		ptr = &(*token)->value[1];
		ft_strcat(buf, ptr);
	}
	else
		ft_strcat(buf, (*token)->value);

}