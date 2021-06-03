/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 14:42:59 by jonny             #+#    #+#             */
/*   Updated: 2021/06/03 11:57:56 by jonny            ###   ########.fr       */
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
# include <dirent.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <errno.h>
# include "../libft/libft.h"
# include "colors.h"
# include <termios.h>

# define BUF_SIZE 4096

# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define CTRL_C 3
# define CTRL_D 4
# define BACKSPACE 127

enum			e_builtin
{
	EXIT = 1,
	EXPORT,
	CD,
	PWD,
	PRINT,
	ENV,
	UNSET
};

enum			e_type
{
	VOID,
	ARG,
	WHITESPACE,
	ESCAPE,
	DOLLAR,
	VAR,
	REDIR,
	APPEND,
	INPUT,
	PIPE,
	SEMICOLON,
	QUOTE,
	DBLQUOTE,
	QUEST
};

enum			e_key
{
	ARROW_UP = 1000,
	ARROW_DOWN
};

typedef struct s_ast
{
	enum e_type		type;
	char			*value;
	struct s_ast	*left;
	struct s_ast	*right;
}				t_ast;

typedef struct s_hist
{
	char			*value;
	struct s_hist	*previous;
	struct s_hist	*next;
}				t_hist;

typedef struct s_state
{
	char			**envp;
	int				code;
	int				fdin;
	int				fdout;
	int				in;
	int				out;
	int				pipefd[2];
	bool			raw_mode;
	t_hist			*history;
	struct termios	termios_new;
	struct termios	termios_backup;

}				t_state;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}				t_env;

typedef struct s_cmd
{
	enum e_type		type[BUF_SIZE];
	char			**args;
	struct s_cmd	*next;
}				t_cmd;

typedef struct s_sig
{
	int		sigint;
	int		sigquit;
	int		pipe;
	int		exit_status;
	pid_t	pid;
	bool	dollar_quote;
	char	buf[BUF_SIZE];
}				t_sig;

extern t_sig	g_sig;

/*
** history
*/

void			hist_update(t_hist **history, char *buffer);
void			free_hist(t_hist **history);

/*
** termios / termcap
*/

char			*ft_readlinev2(t_state *st, char *prompt);
void			clear_buf(void);
void			enable_raw_mode(t_state *st);
void			disable_raw_mode(t_state *st);
void			handle_ctrl_c(char *prompt);
void			handle_ctrl_d(char *c);
void			handle_arrow_up(t_hist **history);
void			handle_arrow_down(t_hist **history);
void			handle_backspace(void);

/*
** redirection
*/

void			parse_redirection(t_state *st, t_cmd *cmd_lst);
void			redir_append(t_state *st, char **args, enum e_type type);
int				input(t_state *st, char **args);
void			init_fds(t_state **st);
void			reset_std(t_state *st);
void			close_fds(t_state *st);
void			ft_close(int fd);

/*
** signal
*/

void			sig_init(char *cmd);
void			handle_signal(int signal);
void			catch_signal(void);

/*
** parsing
*/

void			add_empty_node(t_ast **new_tkn);
void			handle_dbl_quotes(t_ast **token, char *buf, t_env *env_lst);
int				have_whitespaces(char *buf);
void			expand_exit_code(char *buf, t_ast **token);
void			expand_var(char *tmp, t_env *env_lst, t_ast **token);
void			handle_quotes(t_ast **token, char *buf, t_env *env_lst);
int				handle_variables(char *buf, t_ast **token, t_env *env_lst);
void			handle_variables_quotes(char *buf, t_ast **token,
					t_env *env_lst);
void			parse_cmdline(t_state *st, t_env **env_lst, t_cmd *cmd_lst,
					char *input);
t_ast			*parse_args(char *input);
t_ast			*interpreter(t_ast **token, t_env *env_lst, char *buf);
void			parse_cmds(t_ast **token, t_cmd **cmd_lst);
void			token_lst_remove(t_ast **token);
void			has_piped_cmd(t_state *st, t_env *env_lst, t_cmd *cmd_lst);
bool			check_pipe(t_cmd *cmd_lst);
int				parse_semicolon(t_cmd **cmd_lst);
int				file_exists(char *filename);
bool			filepath_exists(t_env *env_lst, t_cmd *cmd_lst);
void			add_new_node(char *buf, t_ast **new_tkn, enum e_type type);
bool			is_ansi_c_quoting(char **str, char c);

/*
** tokenizer
*/

char			*get_next_token(char *input, int *pos);
void			ast_init(t_ast **token, char **buffer);
t_ast			*create_node(char *buffer, enum e_type type);
void			ast_add(t_ast **token, t_ast *new_node);
void			ast_check_type(t_ast **token);
void			free_ast(t_ast **token);

/*
** builtins
*/

int				cd(char *arg, t_env *env_lst);
int				builtin_echo(char **arg, t_cmd *cmd_lst);
void			print_cwd(void);
void			*export_env(t_env **env_lst, char *key, char *value);
int				exit_msh(t_state *status, t_env *env_lst, t_cmd *cmd_lst);
void			print_env_lst(t_env *env_lst);
void			print_export_variables(t_env *env_lst);
void			alpha_sort(char **strs, int len);
int				env_lst_size(t_env *env_lst);
void			builtin_unset(char **variables, t_env **env_lst);

/*
** init_env_lst.c
*/

void			init_env(t_env **env_lst, char **envp);
void			assign_env(char *str, enum e_type type, t_env **env_lst);

/*
** execs
*/

void			cmd_handler(t_state *st, t_env **env_lst, t_cmd *cmd_lst);
int				is_builtin(char *cmd);
void			exec_builtin(int ret, t_state *status, t_env **env_lst,
					t_cmd *cmd_lst);
void			fork_pipes2(t_state *st, t_env *env_lst, int n, t_cmd *cmd_lst);

/*
** utils
*/

char			*ft_readline(t_state *st, t_env *env_lst, char *prompt);
void			print_prompt(char *prompt, char *color);
char			*concat_env(t_env *env_lst);
char			*get_env(t_env *env_lst, char *key);
pid_t			create_fork(pid_t *pid);
void			env_lst_add(t_env **env_lst, t_env *new_env);
void			env_lst_remove(t_env *env_lst, char *key);
void			cmd_lst_add(t_cmd **cmd_lst, t_cmd *new_cmd);
int				cmd_lst_size(t_cmd *cmd_lst);
void			clear_previous_cmd(t_cmd *cmd_lst, t_state *st);
void			free_env_lst(t_env *env_lst);
char			**free_2darray(char **array);
int				tab_size(char **array);
char			*ft_strsep(char **stringp, const char *delim);
bool			is_empty(char *str);
int				ft_isblank(int c);
int				quotes_skip(enum e_type *types, int i);

/*
** error.c
*/

void			error_cases(int errnum, char *cmd, char *arg);
void			error_quotes(void);
void			error_cmd(char *cmd);
int				error_syntax(char *cmd);
void			error_fd(char *arg);

#endif
