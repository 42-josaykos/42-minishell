/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <jonny@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 11:51:53 by jonny             #+#    #+#             */
/*   Updated: 2021/01/04 11:59:10 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/msh.h"

t_sig	g_sig;

void	init_msh(t_state **st, t_env **env_lst, char **envp)
{
	int		lvl;
	char	*tmp;
	char	buf[BUF_SIZE];

	(*st)->in = dup(STDIN);
	(*st)->out = dup(STDOUT);
	lvl = 1;
	tmp = NULL;
	ft_bzero(buf, BUF_SIZE);
	init_fds(st);
	sig_init();
	init_env(env_lst, envp);
	tmp = get_env(*env_lst, "SHLVL");
	if (tmp != NULL)
	{
		lvl = ft_atoi(tmp);
		lvl++;
	}
	tmp = ft_itoa(lvl);
	ft_strlcat(buf, "SHLVL=", BUF_SIZE);
	ft_strlcat(buf, tmp, BUF_SIZE);
	assign_env(buf, env_lst);
	free(tmp);
	ft_printf("Welcome to minishell !\nCtrl-D or \"exit\" to quit.\n");
}

int	get_input(t_state *st, char *input)
{
	char	*line;

	line = ft_readlinev2(st, "minishell ❯ ");
	if (line == NULL)
		return (0);
	ft_strlcpy(input, line, ft_strlen(line));
	free(line);
	return (1);
}

/*
** Returns the env_lst in big single string. Each key=value is
** separated by a '\n' in the string.
*/

char	*concat_env(t_env *env_lst)
{
	int		n;
	t_env	*ptr;
	char	*env;

	n = 0;
	ptr = env_lst;
	while (ptr)
	{
		if (ptr->key && ptr->value)
		{
			n = n + ft_strlen(ptr->key) + ft_strlen(ptr->value) + 2;
		}
		ptr = ptr->next;
	}
	env = ft_calloc(n, sizeof(char));
	while (env_lst)
	{
		if (env_lst->key && env_lst->value)
		{
			ft_strlcat(env, env_lst->key, BUF_SIZE);
			ft_strlcat(env, "=", BUF_SIZE);
			ft_strlcat(env, env_lst->value, BUF_SIZE);
			if (env_lst->next)
				ft_strcat(env, "\n");
		}
		env_lst = env_lst->next;
	}
	return (env);
}

/*
** Infinite loop that call get_input, a function printing a command prompt and
** waiting for an input.
** If input is not an empty, concatenate env_lst in a single string, env
** then split in an array of strings, envp.
*/

void	main_loop(t_state *st, t_env *env_lst, t_cmd *cmd_lst)
{
	char	input[BUF_SIZE];
	char	*env;

	enable_raw_mode(st);
	while (1)
	{
		ft_bzero(input, BUF_SIZE);
		catch_signal();
		get_input(st, input);
		if (!is_empty(input))
		{
			hist_update(&st->history, input);
			env = concat_env(env_lst);
			st->envp = ft_split(env, '\n');
			free(env);
			parse_cmdline(st, env_lst, cmd_lst, input);
			free_2darray(st->envp);
			g_sig.sigint = 0;
			g_sig.sigquit = 0;
			g_sig.pid = 0;
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*env_lst;
	t_cmd	*cmd_lst;
	t_state	*st;

	(void)argv;
	env_lst = NULL;
	cmd_lst = NULL;
	st = NULL;
	if (argc < 2)
	{
		st = ft_calloc(1, sizeof(t_state));
		init_msh(&st, &env_lst, envp);
		main_loop(st, env_lst, cmd_lst);
	}
	else
		printf("Usage: just ./minishell with no arguments.\n");
	return (EXIT_SUCCESS);
}
