/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmdline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 10:22:20 by jonny             #+#    #+#             */
/*   Updated: 2021/02/09 16:33:15 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/msh.h"

void	interpreter(t_state *st, t_ast **token, t_env *env_lst, t_cmd **cmd_lst)
{
	t_ast	*ptr;
	char	buf[MAXCHAR];

	ptr = *token;
	(void)cmd_lst;
	(void)st;
	(void)env_lst;
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
	t_ast	*token;
	char	*buffer[MAXLIST];
	int		pos;
	int		i;

	token = NULL;
	pos = 0;
	i = 0;
	(void)cmd_lst;
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
		interpreter(st, &token, env_lst, &cmd_lst);
		free_ast(&token);
	}
}

int	parse_cmdline(t_state *st, t_env *env_lst, t_cmd *cmd_lst, char *input)
{
	enum e_builtin	ret;

	ret = 0;
	st->path_value = get_env(env_lst, "PATH");
	parse_args(st, env_lst, cmd_lst, input);
	ret = is_builtin(*cmd_lst->args);
	if (ret)
		exec_builtin(ret, st, env_lst, cmd_lst);
	else if (*cmd_lst->args)
		cmd_handler(st->envp, env_lst, cmd_lst);
	return (ret);
}
