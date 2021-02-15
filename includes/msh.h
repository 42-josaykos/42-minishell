/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 14:42:59 by jonny             #+#    #+#             */
/*   Updated: 2021/02/15 15:24:00 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_H
# define MSH_H

# include <errno.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <ctype.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <stdbool.h>
# include "../libft/libft.h"
# include "signal_handler.h"
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

enum	e_type
{
	END,
	BUILTIN,
	EXEC,
	ARG,
	VAR,
	QUOTE,
	DBL_QUOTE,
	SEMICOLON,
	PIPE,
	L_CHEVRON,
	R_CHEVRON,
	DBL_CHEVRON,
	BACKSLASH,
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
	char	*path_value;
	int		code;
	bool	has_semicolon;
	bool	has_pipe;
}				t_state;

typedef struct s_env
{
	char			key[BUF_SIZE];
	char			value[BUF_SIZE];
	struct s_env	*next;
}	t_env;

typedef struct s_cmd
{
	char			cmd[BUF_SIZE];
	char			**args;
	struct s_cmd	*next;
}	t_cmd;

/*
** builtins
*/

int		cd(char *arg, t_env *env_lst);
int		echo(char **arg, t_env *env_lst, int fd);
void	print_cwd(void);
void	*export_env(t_env **env_lst, char *key, char *value);

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
void	free_cmd_lst(t_cmd **cmd_lst);
void	clear_previous_cmd(t_cmd *cmd_lst, t_state *st);
char	*get_env(t_env *env_lst, char *key);
void	cmd_lst_add(t_cmd **cmd_lst, t_cmd *new_cmd);
int		cmd_lst_size(t_cmd *cmd_lst);
pid_t	create_fork(pid_t *pid);
char	**free_2darray(char **tab);
char	*ft_strsep(char **stringp, const char *delim);
bool	is_empty(char *str);

/*
** Error management
*/

void	error_cases(int errnum, char *cmd, char *arg);

/*
** exec_piped_cmd
*/

int		check_semicolon(char *input, t_cmd *cmd_lst);
void	piped_cmd_handler(t_state *status, t_env *env_lst, t_cmd *cmd_lst);
void	exec_last_process(t_state *status, int in, t_cmd *cmd_lst);
void	multi_cmd_handler(t_state *status, t_env *env_lst, t_cmd *cmd_lst);

char	*ft_readline(char *prompt);
int		exit_msh(t_state *status, t_env *env_lst, t_cmd *cmd_lst);
void	free_all(t_state *status, t_env **env_lst, t_cmd **cmd_lst);
void	print_env_lst(char **envp);

/*
** tokenizer
*/
void	ast_init(t_ast **token, char **buffer);
void	free_ast(t_ast **token);
char	*get_next_token(char *input, int *pos);

/*
** parsing
*/

void	parse_cmdline(t_state *st, t_env *env_lst, t_cmd *cmd_lst, char *input);
int		check_pipe(char *input, t_cmd *cmd_lst);
int		file_exists(char *filename);
bool	filepath_exists(t_env *env_lst, t_cmd *cmd_lst);
t_ast	*parse_args(char *input);
void 	has_piped_cmd(t_state *status, t_env *env_lst, char **args);
void	parse_pipe(char *str, t_cmd **cmd_lst);
int	ft_isblank(int c);
#endif
