/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmdline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 10:22:20 by jonny             #+#    #+#             */
/*   Updated: 2021/02/09 16:06:42 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/msh.h"
#include "../tests/ast.h"

void interpret_cmd(t_state *st, t_ast **token, t_env *env_lst, t_cmd **cmd_lst)
{
	(void)cmd_lst;
	(void)st;
	(void)env_lst;
	t_ast *ptr;
	ptr = *token;
	char  buf[MAXCHAR];
	if (!ft_strncmp(ptr->value, ";", 2))
	{
		ft_putstr_fd("bash: syntax error near unexpected token `;'\n", STDERR);
		return ;
	}
	ft_bzero(buf, MAXCHAR);
	while (ptr)
	{
		if (ptr->type == BUILTIN || ptr->type == EXEC)
		{
			ft_strcat(buf, ptr->value);
			ft_strcat(buf, " ");
		}
		ptr = ptr->right;
	}
	(*cmd_lst)->args = ft_split(buf, ' ');
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

int	parse_cmdline(t_state *st, t_env *env_lst, t_cmd *cmd_lst, char *input)
{
	enum e_builtin	ret;

	ret = 0;
	st->path_value = get_env(env_lst, "PATH");
	parse_args(st, env_lst, cmd_lst, input);
	ret = is_builtin(cmd_lst->args[0]);
	if (ret)
		exec_builtin(ret, st, env_lst, cmd_lst);
	else if (*cmd_lst->args)
		cmd_handler(st->envp, env_lst, cmd_lst);
	return (ret);
}
