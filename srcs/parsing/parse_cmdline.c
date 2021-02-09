/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmdline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 10:22:20 by jonny             #+#    #+#             */
/*   Updated: 2021/02/09 14:12:53 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/msh.h"
#include "../tests/ast.h"

void interpret_cmd(t_state *st, t_ast **token, t_env *env_lst, t_cmd **cmd_lst)
{
	(void)cmd_lst;
	(void)st;
	(void)env_lst;
	// char *parsed[MAXCHAR];
	t_ast *ptr;
	ptr = *token;
	if (!ft_strncmp(ptr->value, ";", 2))
	{
		ft_putstr_fd("bash: syntax error near unexpected token `;'\n", STDERR);
		return ;
	}
}

void	parse_args(t_state *st, t_env *env_lst, t_cmd *cmd_lst, char *input)
{
	(void)cmd_lst;
	t_ast *token = NULL;

	int pos = 0;
	int i = 0;
	char *buffer[MAXLIST];
	ft_bzero(buffer, MAXLIST);
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
		interpret_cmd(st, &token, env_lst, &cmd_lst);
		free_ast(&token);
	}
}

/*
** Check the input.
** Returns 1 if "exit".
** Returns 2 if "export" command (debug test).
** Returns 3 if "cd".
** Check each path directories for the executable and execute it (cmd_handler).
*/

int	parse_cmdline(t_state *st, t_env *env_lst, t_cmd *cmd_lst, char *input)
{
	enum e_builtin	ret;

	ret = 0;
	st->path_value = get_env(env_lst, "PATH");
	// if (check_semicolon(input, cmd_lst))
	// {
		// multi_cmd_handler(status, env_lst, cmd_lst);
		// return (0);
	// }
	// else if (check_pipe(input, cmd_lst))
	// {
		// piped_cmd_handler(status, env_lst, cmd_lst);
		// return (0);
	// }
	// else
		parse_args(st, env_lst, cmd_lst, input);
	ret = is_builtin(cmd_lst->args[0]);
	if (ret)
		exec_builtin(ret, st, env_lst, cmd_lst);
	else if (*cmd_lst->args)
		cmd_handler(st->envp, env_lst, cmd_lst->args);
	return (ret);
}
