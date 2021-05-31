/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmdline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 10:22:20 by jonny             #+#    #+#             */
/*   Updated: 2021/05/31 17:22:33 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/msh.h"

t_ast	*parse_args(char *input)
{
	t_ast	*token;
	char	*buffer[BUF_SIZE];
	int		pos;
	int		i;

	token = NULL;
	pos = 0;
	i = 0;
	while (i < BUF_SIZE)
	{
		buffer[i] = NULL;
		i++;
	}
	i = 0;
	if (input)
	{
		while (input[pos])
		{
			buffer[i] = get_next_token(input, &pos);
			i++;
		}
		ast_init(&token, buffer);
	}
	return (token);
}

int	is_invalid_type(enum e_type *types, int i)
{
	if (i == 0 && (!types[i + 1] || (types[i] == PIPE
				|| types[i] == SEMICOLON)))
		return (1);
	else if (types[i] == SEMICOLON && (types[i + 1] == PIPE))
		return (1);
	else if (types[i] == SEMICOLON && (types[i + 1] != SEMICOLON))
		return (0);
	else if (((types[i + 1] == REDIR
				|| types[i + 1] == APPEND || types[i + 1] == INPUT
				|| types[i + 1] == PIPE || types[i + 1] == SEMICOLON)))
		return (1);
	return (0);
}

static int	test_syntax_error(enum e_type *types)
{
	int	i;

	i = 0;
	while (types[i] != VOID)
	{
		if (types[i] == DBLQUOTE || types[i] == QUOTE)
			i += quotes_skip(types, i);
		if (types[i] == SEMICOLON && is_invalid_type(types, i))
			return (error_syntax(";"));
		else if (types[i] == PIPE && is_invalid_type(types, i))
			return (error_syntax("|"));
		else if (types[i] == REDIR && is_invalid_type(types, i))
			return (error_syntax(">"));
		else if (types[i] == APPEND && is_invalid_type(types, i))
			return (error_syntax(">>"));
		else if (types[i] == INPUT && is_invalid_type(types, i))
			return (error_syntax("<"));
		i++;
	}
	return (0);
}

int	has_syntax_error(t_ast *token)
{
	char		str[3];
	enum e_type	types[BUF_SIZE];
	int			i;
	t_ast		*ptr;

	ft_bzero(str, 3);
	ft_bzero(types, BUF_SIZE);
	i = 0;
	ptr = token;
	while (ptr)
	{
		if (ptr->type != WHITESPACE)
		{
			types[i] = ptr->type;
			i++;
		}
		ptr = ptr->right;
	}
	return (test_syntax_error(types));
}

void	parse_cmdline(t_state *st, t_env **env_lst, t_cmd *cmd_lst,
															char *input)
{
	t_ast	*tmp;
	t_ast	*token;
	char	buf[BUF_SIZE];

	ft_bzero(buf, BUF_SIZE);
	tmp = parse_args(input);
	if (has_syntax_error(tmp))
	{
		free_ast(&tmp);
		return ;
	}
	while (tmp && !g_sig.sigint)
	{
		token = interpreter(&tmp, *env_lst, buf);
		token_lst_remove(&tmp);
		parse_cmds(&token, &cmd_lst);
		cmd_handler(st, env_lst, cmd_lst);
		clear_previous_cmd(cmd_lst, NULL);
		free(cmd_lst);
		if (g_sig.exit_status == 130)
			break ;
	}
}
