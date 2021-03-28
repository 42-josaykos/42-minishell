/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmdline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 10:22:20 by jonny             #+#    #+#             */
/*   Updated: 2021/03/28 14:52:20 by jonny            ###   ########.fr       */
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

int	has_syntax_error(t_ast *token)
{
	char	str[3];

	ft_bzero(str, 3);
	while (token)
	{
		if (token->type == SEMICOLON && (!token->left
				|| (token->left && token->left->type != ARG)))
			return (error_syntax(token->value));
		if (token->type == PIPE && token->left && token->left->type != ARG)
			return (error_syntax(token->value));
		if (token->type == REDIR && token->left && token->left->type != ARG)
			return (error_syntax(token->value));
		if (token->type == APPEND && token->left && token->left->type != ARG)
			return (error_syntax(token->value));
		token = token->right;
	}
	return (0);
}

void	parse_cmdline(t_state *st, t_env *env_lst, t_cmd *cmd_lst, char *input)
{
	t_ast	*tmp;
	t_ast	*token;

	tmp = parse_args(input);
	if (tmp != NULL)
	{
		token = interpreter(tmp, env_lst);
		free_ast(&tmp);
		if (has_syntax_error(token))
		{
			free_ast(&token);
			return ;
		}
		while (token)
		{
			parse_cmds(&token, &cmd_lst, env_lst);
			cmd_handler(st, env_lst, cmd_lst);
			clear_previous_cmd(cmd_lst, NULL);
			free(cmd_lst);
		}
	}
}
