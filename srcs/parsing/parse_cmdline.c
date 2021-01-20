/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmdline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 10:22:20 by jonny             #+#    #+#             */
/*   Updated: 2021/01/20 15:48:41 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

void	parse_args(char *str, char **args)
{
	int	i;

	i = 0;
	while (i < 100)
	{
		args[i] = ft_strsep(&str, " \t");
		if (args[i] == NULL)
			break ;
		if (strlen(args[i]) == 0)
			i--;
		i++;
	}
}

/*
** Check the input.
** Returns 1 if "exit".
** Returns 2 if "export" command (debug test).
** Returns 3 if "cd".
** Check each path directories for the executable and execute it (cmd_handler).
*/

int	parse_cmdline(t_env *env_lst, t_cmd *cmd_lst, char *input)
{
	int	ret;

	ret = 0;
	if (check_pipe(input, cmd_lst))
	{
		printf("input has | cmds but need a function to handle it!\n");
		return (0);
	}
	// else if (check_semicolon(input, cmd_lst))
	// {
		// return (0);
	// }
	else
		parse_args(input, cmd_lst->args);
	ret = is_builtin(cmd_lst->args[0]);
	if (!ret)
		cmd_handler(env_lst, cmd_lst->args);
	return (ret);
}
