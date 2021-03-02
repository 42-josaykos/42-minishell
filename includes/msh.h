/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 14:42:59 by jonny             #+#    #+#             */
/*   Updated: 2021/03/02 12:14:42 by jonny            ###   ########.fr       */
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
# include "colors.h"

# define BUF_SIZE 2048

# define STDIN 0
# define STDOUT 1
# define STDERR 2

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

enum e_type
{
	ARG,
	REDIR
};

typedef struct s_ast
{
	enum e_type		type;
	char			*value;
	struct s_ast	*left;
	struct s_ast	*right;
}				t_ast;

typedef struct s_state
{
	char	**envp;
	int		code;
	bool	has_semicolon;
	bool	has_pipe;
	int		dbl_quotes;
	int		redir;
	int		fdin;
	int		fdout;
	int		in;
	int		out;
}				t_state;

typedef struct s_env
{
	char			key[BUF_SIZE];
	char			value[BUF_SIZE];
	struct s_env	*next;
}	t_env;

typedef struct s_cmd
{
	char			**args;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_sig
{
	int		sigint;
	int		sigquit;
	int		exit_status;
	pid_t	pid;
}				t_sig;

extern t_sig	g_sig;

void    init_fds(t_state **st);
void	reset_std(t_state *st);
void	close_fds(t_state *st);
void	ft_close(int fd);

void	sig_init(void);
void	handle_signal(int signal);
void	catch_signal(void);

/*
** builtins
*/

int		cd(char *arg, t_env *env_lst);
int		echo(char **arg, t_env *env_lst, int fd);
void	print_cwd(void);
void	*export_env(t_env **env_lst, char *key, char *value);
int		exit_msh(t_state *status, t_env *env_lst, t_cmd *cmd_lst);

/*
** init_env_lst.c
*/

void	init_env(t_env **env_lst, char **envp);
void	assign_env(char *str, t_env **env_lst);

/*
** Commands executions
*/

void	cmd_handler(t_state *st, t_env *env_lst, t_cmd *cmd_lst);
int		is_builtin(char *cmd);
void	exec_builtin(int ret, t_state *status, t_env *env_lst, t_cmd *cmd_lst);

/*
** utils
*/

void	env_lst_add(t_env **env_lst, t_env *new_env);
void	env_lst_remove(t_env *env_lst, char *key);
void	free_env_lst(t_env **env_lst);
void	clear_previous_cmd(t_cmd *cmd_lst, t_state *st);
char	*get_env(t_env *env_lst, char *key);
void	cmd_lst_add(t_cmd **cmd_lst, t_cmd *new_cmd);
int		cmd_lst_size(t_cmd *cmd_lst);
int		ft_isblank(int c);
pid_t	create_fork(pid_t *pid);
char	**free_2darray(char **tab);
char	*ft_strsep(char **stringp, const char *delim);
bool	is_empty(char *str);

/*
** Error management
*/

void	error_cases(int errnum, char *cmd, char *arg);
void	error_quotes(void);
void	error_cmd(char *cmd);

/*
**
*/

char	*ft_readline(char *prompt);
void	print_env_lst(char **envp);
void	ast_init(t_ast **token, char **buffer);
void	free_ast(t_ast **token);
char	*get_next_token(char *input, int *pos);
void	parse_cmdline(t_state *st, t_env *env_lst, t_cmd *cmd_lst, char *input);
int		file_exists(char *filename);
bool	filepath_exists(t_env *env_lst, t_cmd *cmd_lst);
t_ast	*parse_args(char *input);
void	has_piped_cmd(t_state *status, t_env *env_lst, char **args);
void	parse_pipe(char *str, t_cmd **cmd_lst);
int		ft_isblank(int c);
bool	check_pipe(char **str);
int		parse_semicolon(t_cmd **cmd_lst);
char	**interpreter_loop(t_state *st, t_ast **token, t_env *env_lst);

#endif