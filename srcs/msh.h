/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <jonny@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 14:42:59 by jonny             #+#    #+#             */
/*   Updated: 2021/01/15 16:53:37 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_H
# define MSH_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <stdbool.h>
# include "../libft/libft.h"

# define MAXCHAR 100
# define EXIT 1
# define EXPORT 2
# define CD 3

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

/*
** Cmd parsing
*/

int		parse_cmdline(t_env *env_lst, t_cmd *cmd_lst, char *input);
void	parse_args(char *str, char **args);
int		file_exists(char *filename);
void	read_path(t_env *env_lst, char *filepath);

/*
**  Path initialization, export env and free memory
*/

void	init_path(int fd, t_env **env_lst);
void	export_env(t_env **env_lst, char *key, char *value);
void	free_env_lst(t_env **env_lst);
int		cd(char *arg);
void	parse_path(t_env *env_lst);

/*
** Commands executions
*/

void	exec_cmd(char *filepath);
void	cmd_handler(t_env *env_lst, char *input);
void	exec_syscmd(char *input);

/*
** String utils
*/

char	*ft_strsep(char **stringp, const char *delim);

/*
** parsing cmd pipes
*/

int		check_pipe(char *input, t_cmd *cmd_lst);
void	free_cmd_lst(t_cmd **cmd_lst);

/*
** Tests
*/

void	execArgsPiped(t_cmd *cmd_lst);

#endif
