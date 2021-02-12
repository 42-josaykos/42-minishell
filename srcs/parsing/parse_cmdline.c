/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmdline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 10:22:20 by jonny             #+#    #+#             */
/*   Updated: 2021/02/12 15:56:40 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/msh.h"

bool is_semicolon(t_ast *token, t_cmd **cmd_lst)
{
	t_cmd *new_cmd;
	if (!ft_strncmp(token->value, ";", 2))
	{
		new_cmd = ft_calloc(1, sizeof(t_cmd));
		new_cmd->next = NULL;
		cmd_lst_add(cmd_lst, new_cmd);
		return (true);
	}
	return (false);
}

void	interpreter(t_state *st, t_ast **token, t_env *env_lst, t_cmd **cmd_lst)
{
	t_ast	*ptr;
	t_cmd	*cmd;
	char	buf[BUF_SIZE];

	ptr = *token;
	cmd = *cmd_lst;
	(void)st;
	(void)env_lst;
	if (!ft_strncmp(ptr->value, ";", 2))
	{
		ft_putstr_fd("bash: syntax error near unexpected token `;'\n", STDERR);
		return ;
	}
	ft_bzero(buf, BUF_SIZE);
	while (ptr)
	{
		if (is_semicolon(ptr, cmd_lst))
		{
			st->has_semicolon = true;
			cmd->args = split_whitespace(buf);
			cmd = cmd->next;
			ft_bzero(buf, BUF_SIZE);
		}
		else if (ptr->type == BUILTIN || ptr->type == EXEC)
		{
			ft_strcat(buf, ptr->value);
			ft_strcat(buf, " ");
		}
		ptr = ptr->right;
	}
	cmd->args = split_whitespace(buf);
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
			// printf("tokens[%d] = \"%s\"\n", i, buffer[i]);
			i++;
		}
		ast_init(&token, buffer);
		// for(t_ast *ptr = token; ptr != NULL ; ptr = ptr->right)
			// printf("token = \"%s\"\n", ptr->value);
	}
	return (token);
}

int	parse_cmdline(t_state *st, t_env *env_lst, t_cmd *cmd_lst, char *input)
{
	enum e_builtin	ret;
	t_ast	*token;

	ret = 0;
	st->path_value = get_env(env_lst, "PATH");
	token = parse_args(input);
	if (token != NULL)
	{
		interpreter(st, &token, env_lst, &cmd_lst);
		free_ast(&token);
		if (cmd_lst->args)
		{
			ret = is_builtin(*cmd_lst->args);
			if (ret)
				exec_builtin(ret, st, env_lst, cmd_lst);
			else if (*cmd_lst->args)
				cmd_handler(st, env_lst, cmd_lst);
		}
	}
	return (ret);
}
