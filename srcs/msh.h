/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 14:42:59 by jonny             #+#    #+#             */
/*   Updated: 2021/01/20 15:22:52 by jonny            ###   ########.fr       */
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

# define MAXCHAR 1000
# define EXIT 1
# define EXPORT 2
# define CD 3
# define PWD 4

typedef struct s_env
{
	char			key[MAXCHAR];
	char			value[MAXCHAR];
	struct s_env	*next;
}	t_env;

typedef struct s_cmd
{
	char			*args[MAXCHAR];
	struct s_cmd	*next;
}	t_cmd;

int		cd(char *arg, t_env *env_lst);
void	*export_env(t_env **env_lst, char *key, char *value);
int		file_exists(char *filename);
void	print_cwd(void);

/*
** parse_cmdline.c
*/

int		parse_cmdline(t_env *env_lst, t_cmd *cmd_lst, char *input);
void	parse_args(char *str, char **args);

/*
** init_env_lst.c
*/

void	init_env(t_env **env_lst, char **envp);

/*
** Commands executions
*/

void	cmd_handler(t_env *env_lst, char **args);
int		is_builtin(char *cmd);
void	exec_builtin(int ret, t_env *env_lst, t_cmd *cmd_lst);

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

/*
** Error management
*/

void	error_cases(int errnum, char *cmd, char *arg);

/*
** Error management
*/

void	check_semicolon(char *input, t_cmd *cmd_lst);

#endif
