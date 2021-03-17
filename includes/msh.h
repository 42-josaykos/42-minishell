/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 14:42:59 by jonny             #+#    #+#             */
/*   Updated: 2021/03/17 11:05:55 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_H
# define MSH_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <errno.h>
# include "../libft/libft.h"
# include "colors.h"
# include <term.h>
# include <curses.h>
# include <termios.h>

# define BUF_SIZE 4096

# define STDIN 0
# define STDOUT 1
# define STDERR 2

enum e_builtin
{
	EXIT = 1,
	EXPORT,
	CD,
	PWD,
	PRINT,
	ENV,
	UNSET
};

enum e_type
{
	VOID,
	ARG,
	WHITESPACE,
	ESCAPE,
	DOLLAR,
	VARIABLE,
	REDIR,
	APPEND,
	INPUT,
	PIPE,
	SEMICOLON,
	QUOTE,
	DBLQUOTE,
	CONCAT,
	QUESTION
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
	char			**envp;
	int				code;
	int				fdin;
	int				fdout;
	int				in;
	int				out;
	int				pipefd[2];
	char			*term_type;
	bool			raw_mode;
	struct termios	termios_new;
	struct termios	termios_backup;

}				t_state;

typedef struct s_env
{
	char			key[BUF_SIZE];
	char			value[BUF_SIZE];
	struct s_env	*next;
}	t_env;

typedef struct s_cmd
{
	enum e_type		type[BUF_SIZE];
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

/*
** termcap
*/

void	enable_raw_mode(t_state *st, t_env *env_lst);
void	disable_raw_mode(t_state *st);

/*
** redirection
*/

void	parse_redirection(t_state *st, t_cmd *cmd_lst);
void	redir_append(t_state *st, char **args, enum e_type type);
void	input(t_state *st, char **args);
void	init_fds(t_state **st);
void	reset_std(t_state *st);
void	close_fds(t_state *st);
void	ft_close(int fd);

/*
** signal
*/

void	sig_init(void);
void	handle_signal(int signal);
void	catch_signal(void);

/*
** parsing
*/

void	parse_cmdline(t_state *st, t_env *env_lst, t_cmd *cmd_lst, char *input);
t_ast	*parse_args(char *input);
t_ast	*interpreter(t_ast *token, t_env *env_lst);
bool	parse_cmds(t_ast *token, t_cmd **cmd_lst);
void	has_piped_cmd(t_state *st, t_env *env_lst, t_cmd *cmd_lst);
void	parse_pipe(int i, int j, t_cmd *cmd_Lst, t_cmd **piped);
bool	check_pipe(char **str);
int		parse_semicolon(t_cmd **cmd_lst);
int		file_exists(char *filename);
bool	filepath_exists(t_env *env_lst, t_cmd *cmd_lst);

/*
** tokenizer
*/

char	*get_next_token(char *input, int *pos);
void	ast_init(t_ast **token, char **buffer);
t_ast	*create_node(char *buffer, enum e_type type);
void	ast_add(t_ast **token, t_ast *new_node);
void	ast_check_type(t_ast **token);
void	free_ast(t_ast **token);

/*
** builtins
*/

int		cd(char *arg, t_env *env_lst);
int		builtin_echo(char **arg, t_env *env_lst, int fd);
void	print_cwd(void);
void	*export_env(t_env **env_lst, char *key, char *value);
int		exit_msh(t_state *status, t_env *env_lst, t_cmd *cmd_lst);
void	print_env_lst(char **envp);

/*
** init_env_lst.c
*/

void	init_env(t_env **env_lst, char **envp);
void	assign_env(char *str, t_env **env_lst);

/*
** execs
*/

void	cmd_handler(t_state *st, t_env *env_lst, t_cmd *cmd_lst);
int		is_builtin(char *cmd);
void	exec_builtin(int ret, t_state *status, t_env *env_lst, t_cmd *cmd_lst);

/*
** utils
*/

char	*ft_readline(t_state *st, t_env *env_lst, char *prompt);
void	print_prompt(char *prompt, char *color);
char	*get_env(t_env *env_lst, char *key);
pid_t	create_fork(pid_t *pid);
void	env_lst_add(t_env **env_lst, t_env *new_env);
void	env_lst_remove(t_env *env_lst, char *key);
void	cmd_lst_add(t_cmd **cmd_lst, t_cmd *new_cmd);
int		cmd_lst_size(t_cmd *cmd_lst);
void	clear_previous_cmd(t_cmd *cmd_lst, t_state *st);
void	free_env_lst(t_env **env_lst);
char	**free_2darray(char **array);
int		tab_size(char **array);
char	*ft_strsep(char **stringp, const char *delim);
bool	is_empty(char *str);
int		ft_isblank(int c);

/*
** error.c
*/

void	error_cases(int errnum, char *cmd, char *arg);
void	error_quotes(void);
void	error_cmd(char *cmd);
int		error_syntax(char *cmd);
void	error_fd(char *arg);

#endif