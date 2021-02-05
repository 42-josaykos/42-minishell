/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 14:42:59 by jonny             #+#    #+#             */
/*   Updated: 2021/02/05 16:46:25 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_H
# define MSH_H

# include <errno.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <stdbool.h>
# include "../libft/libft.h"
# include "signal_handler.h"
# include "colors.h"

# define MAXCHAR 1024
# define MAXLIST 128

enum e_builtin
{
	EXIT = 1,
	EXPORT,
	CD,
	PWD,
	ECHO,
	ENV,
	UNSET
};

typedef struct s_state
{
	char	**envp;
	int		code;
}				t_state;

typedef struct s_env
{
	char			key[MAXCHAR];
	char			value[MAXCHAR];
	struct s_env	*next;
}	t_env;

typedef struct s_cmd
{
	char			cmd[MAXCHAR];
	char			*args[MAXCHAR];
	struct s_cmd	*next;
}	t_cmd;

void	*export_env(t_env **env_lst, char *key, char *value);
int		file_exists(char *filename);

/*
** builtins
*/

int		cd(char *arg, t_env *env_lst);
int		echo(char **arg, t_env *env_lst, int fd);
void	print_cwd(void);

/*
** parse_cmdline.c
*/

int		parse_cmdline(t_state *status, t_env *env_lst, t_cmd *cmd_lst, char *input);
void	parse_args(char *str, t_cmd *cmd_lst);

/*
** init_env_lst.c
*/

void	init_env(t_env **env_lst, char **envp);
void	assign_env(char *str, t_env **env_lst);

/*
** Commands executions
*/

void	cmd_handler(char **envp, t_env *env_lst, char **args);
int		is_builtin(char *cmd);
void	exec_builtin(int ret, t_state *status, t_env *env_lst, t_cmd *cmd_lst);

/*
** string_utils.c
*/

char	*ft_strsep(char **stringp, const char *delim);
bool	is_empty(char *str);

/*
** parse_pipe.c
*/

int		check_pipe(char *input, t_cmd *cmd_lst);

/*
** list_utils.c && list_utils2.c
*/
void	env_lst_add(t_env **env_lst, t_env *new_env);
void	env_lst_remove(t_env *env_lst, char *key);
void	free_env_lst(t_env **env_lst);
void	free_cmd_lst(t_cmd **cmd_lst);
void	clear_previous_cmd(t_cmd *cmd_lst);
char	*get_env(t_env *env_lst, char *key);
void	cmd_lst_add(t_cmd **cmd_lst, t_cmd *new_cmd);
int		cmd_lst_size(t_cmd *cmd_lst);
pid_t	create_fork(pid_t *pid);
char	**free_2darray(char **tab);

/*
** Error management
*/

void	error_cases(int errnum, char *cmd, char *arg);

/*
** exec_piped_cmd
*/

int		check_semicolon(char *input, t_cmd *cmd_lst);
void	piped_cmd_handler(char **envp, t_env *env_lst, t_cmd *cmd_lst);
void	exec_last_process(char **envp, int in, t_cmd *cmd_lst);
void	multi_cmd_handler(t_state *status, t_env *env_lst, t_cmd *cmd_lst);

char	*ft_readline(char *prompt);
int		exit_msh(t_state *status, t_env **env_lst, t_cmd **cmd_lst);
void	free_all(t_state *status, t_env **env_lst, t_cmd **cmd_lst);
void	print_env_lst(char **envp);
#endif
