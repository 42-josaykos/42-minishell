/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <jonny@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 11:51:53 by jonny             #+#    #+#             */
/*   Updated: 2021/01/04 11:40:25 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/msh.h"

/*
** Prints a welcome message.
** Create a list of env variables.
** TODO: Need to handle mutliple variables in the config file (.mshrc)
*/

void	init_msh(t_env **env_lst, char **envp)
{
	ft_printf("Welcome to minishell !\nCtrl-C or \"exit\" to quit.\n");
	init_env(env_lst, envp);
}

int	get_input(char *input)
{
	char	*line;

	line = NULL;
	ft_printf("%sminishell $ %s", BOLD_MAGENTA, RESET);
	get_next_line(0, &line);
	ft_strlcpy(input, line, MAXCHAR);
	free(line);
	return (0);
}

char	*concat_env(t_env *env_lst)
{
	int		n;
	t_env	*ptr;
	char	*env;

	n = 0;
	ptr = env_lst;
	while (ptr)
	{
		n = n + ft_strlen(ptr->key) + ft_strlen(ptr->value) + 2;
		ptr = ptr->next;
	}
	env = ft_calloc(n, sizeof(char));
	while (env_lst)
	{
		ft_strcat(env, env_lst->key);
		ft_strcat(env, "=");
		ft_strcat(env, env_lst->value);
		if (env_lst->next)
			ft_strcat(env, "\n");
		env_lst = env_lst->next;
	}
	return (env);
}

/*
** Infinite loop that call get_input, a function printing a command prompt and
** waiting for an input.
** TODO: Need to call functions for parsing the input string
*/

void	main_loop(char *env, t_env *env_lst, t_cmd *cmd_lst)
{
	char	input[MAXCHAR];
	int		ret;

	ret = 0;
	while (1)
	{
		get_input(input);
		if (ft_strncmp(input, "", 1) && !is_empty(input))
		{
			env = concat_env(env_lst);
			ret = parse_cmdline(env_lst, cmd_lst, input);
			free(env);
		}
		if (ret == EXIT)
			break ;
		clear_previous_cmd(cmd_lst);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*env_lst;
	t_cmd	*cmd_lst;
	char	*env;

	(void)argv;
	env_lst = NULL;
	cmd_lst = NULL;
	env = NULL;
	if (argc < 2)
	{
		init_msh(&env_lst, envp);
		cmd_lst = ft_calloc(1, sizeof(t_cmd));
		main_loop(env, env_lst, cmd_lst);
	}
	else
		printf("Usage: just ./minishell with no arguments.\n");
	free_env_lst(&env_lst);
	free_cmd_lst(&cmd_lst);
	free(env);
	return (EXIT_SUCCESS);
}
