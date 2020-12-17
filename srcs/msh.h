/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <jonny@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 14:42:59 by jonny             #+#    #+#             */
/*   Updated: 2020/12/17 13:31:05 by jonny            ###   ########.fr       */
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

typedef struct		s_env
{
	char			key[MAXCHAR];
	char			value[MAXCHAR];
	struct s_env	*next;
}					t_env;

/*
** Cmd parsing
*/

int					parse_cmdline(t_env *env_lst, char *input);
int					file_exists(char *filename);
void				read_path(t_env *env_lst, char *filepath);

/*
**  Path initialization, export env and free memory
*/

void				init_path(int fd, t_env **env_lst);
void				export_env(t_env **env_lst, char *key, char *value);
void				free_env_lst(t_env **env_lst);
int         cd(char *arg);
void        parse_path(t_env *env_lst);

/*
** Commands executions  
*/

void        exec_cmd(t_env *env_lst, char *filename);
void        exec_syscmd(char *input);

#endif
