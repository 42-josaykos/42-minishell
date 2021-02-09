/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmdline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 10:22:20 by jonny             #+#    #+#             */
/*   Updated: 2021/02/08 17:24:34 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/msh.h"
#include "../tests/ast.h"
#include <stdio.h>

void	parse_args(char *str, t_cmd *cmd_lst)
{
	(void)cmd_lst;
	t_ast *token = NULL;

	int pos = 0;
	int i = 0;
	char *buffer[MAXLIST];
	ft_bzero(buffer, MAXLIST);
	if (str)
	{
		while (str[pos])
		{
			buffer[i] = get_next_token(str, &pos);
			// printf("tokens[%d] = \"%s\"\n", i, buffer[i]);
			i++;
		}
		ast_init(&token, buffer);
		for(t_ast *ptr = token; ptr != NULL ; ptr = ptr->right)
			printf("token = \"%s\"\n", ptr->value);
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

int	parse_cmdline(t_state *status, t_env *env_lst, t_cmd *cmd_lst, char *input)
{
	enum e_builtin	ret;

	ret = 0;
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
		parse_args(input, cmd_lst);
	ret = is_builtin(cmd_lst->args[0]);
	if (ret)
		exec_builtin(ret, status, env_lst, cmd_lst);
	else if (*cmd_lst->args)
		cmd_handler(status->envp, env_lst, cmd_lst->args);
	return (ret);
}
