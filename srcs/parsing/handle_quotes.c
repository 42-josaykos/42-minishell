/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 17:38:04 by jonny             #+#    #+#             */
/*   Updated: 2021/06/03 11:58:36 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/msh.h"

static void	handle_quotes2(t_ast **token, char *buf)
{
	char	*ptr;
	char	*str;
	char	c;

	ptr = NULL;
	str = "\0";
	if ((*token)->value[0] == '\\' && (*token)->right && g_sig.dollar_quote)
	{
		c = (*token)->right->value[0];
		if (is_ansi_c_quoting(&str, c))
		{
			ft_strcat(buf, str);
			token_lst_remove(token);
			ptr = &(*token)->value[1];
			ft_strcat(buf, ptr);
		}
		else
			ft_strcat(buf, (*token)->value);
	}
	else if ((*token)->value[0] != '\'')
		ft_strcat(buf, (*token)->value);
}

int	handle_first_quote(t_ast **token, char *buf,
														enum e_type *type)
{
	int	len;

	len = ft_strlen(buf);
	if (*token)
	{
		*type = (*token)->type;
		if (buf[len - 1] == '=')
		{
			ft_strcat(buf, (*token)->value);
			token_lst_remove(token);
			return (1);
		}
		else
			token_lst_remove(token);
	}
	return (0);
}

void	change_type(t_ast **token)
{
	t_ast	*ptr;

	ptr = *token;
	while (ptr)
	{
		if (!ft_strncmp(ptr->value, "\'", 2))
		{
			ptr->type = QUOTE;
			break ;
		}
		ptr->type = ARG;
		ptr = ptr->right;
	}
}

void	handle_quotes(t_ast **token, char *buf, t_env *env_lst)
{
	enum e_type	type;

	type = QUOTE;
	handle_first_quote(token, buf, &type);
	if (type == QUOTE)
		change_type(token);
	while (*token)
	{
		if ((*token)->type == DOLLAR)
			g_sig.dollar_quote = true;
		if (type == DBLQUOTE)
			handle_dbl_quotes(token, buf, env_lst);
		else if (type == QUOTE)
			handle_quotes2(token, buf);
		if ((*token)->type == type)
			break ;
		token_lst_remove(token);
	}
	g_sig.dollar_quote = false;
}
