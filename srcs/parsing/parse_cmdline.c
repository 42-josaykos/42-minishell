/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmdline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 10:22:20 by jonny             #+#    #+#             */
/*   Updated: 2021/03/02 14:39:03 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/msh.h"

int	test_quotes(char *str)
{
	int	quotes;
	int	dquotes;
	int	i;

	i = 0;
	quotes = 0;
	dquotes = 0;
	while (str[i])
	{
		if (str[i] == '\"')
			dquotes += 1;
		if (str[i] == '\'')
			quotes += 1;
		i++;
	}
	if (dquotes % 2 || quotes % 2)
		error_quotes();
	else
		return (1);
	return (0);
}

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

void	parse_cmdline(t_state *st, t_env *env_lst, t_cmd *cmd_lst, char *input)
{
	t_ast	*token;
	int		ret;

	if (!test_quotes(input))
		return ;
	token = parse_args(input);
	if (token != NULL)
	{
		if (!ft_strncmp(token->value, ";", 2))
		{
			ft_putstr_fd("msh: syntax error near unexpected token `;'", STDERR);
			write(STDERR, "\n", 1);
			free_ast(&token);
			return ;
		}
		// cmd_lst->args = interpreter_loop(st, &token, env_lst);
		cmd_lst->args = interpreter(st, token, env_lst);
		ret = parse_semicolon(&cmd_lst);
		free_ast(&token);
		if (cmd_lst->args && *cmd_lst->args && !is_empty(*cmd_lst->args))
			cmd_handler(st, env_lst, cmd_lst);
		clear_previous_cmd(cmd_lst, NULL);
		if (ret)
			free(cmd_lst);
	}
}
