/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 12:21:20 by jonny             #+#    #+#             */
/*   Updated: 2021/01/20 11:11:21 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

/*
** Create a child process and execute the command in it. Parent process waits
** the child process to finish. read_path() reads the PATH and put it in the
** filepath[MAXCHAR] buffer. We add the filename to the path with ft_strcat()
*/

void	exec_cmd(char *filepath, char **args)
{
	pid_t	p1;
	
	args[0] = filepath;
	p1 = fork();
	if (p1 < 0)
	{
		ft_printf("Cannot execute child process.\n");
		exit(-1);
	}
	if (p1 == 0)
	{
		execve(*args, args, NULL);
		exit(0);
	}
	wait(NULL);
}

/*
** Split PATH and look in each filepath for the command.
** If found, execute the command. 
*/

static void	*cmd_handler2(char *ptr, char **args)
{
	char	filepath[MAXCHAR];
	char	*tmp;
	int		len;

	len = 0;
	while (ptr)
	{
		tmp = ft_strsep(&ptr, ":");
		len = ft_strlen(tmp);
		ft_strlcpy(filepath, tmp, len + 1);
		if (filepath[len - 1] != '/')
			ft_strcat(filepath, "/");
		ft_strcat(filepath, args[0]);
		if (file_exists(filepath) == 0)
		{
			printf(">>> Executing %s >>>\n", filepath);
			exec_cmd(filepath, args);
			return (ptr);
		}
	}
	return (ptr);
}

/*
** Iterate through the env list for PATH, then try each filepath.
*/

void	cmd_handler(t_env *env_lst, char **args)
{
	char	*ptr;
	char	copy[MAXCHAR];

	ptr = NULL;
	while (env_lst)
	{
		if (!ft_strncmp(env_lst->key, "PATH", 4))
		{
			ft_strlcpy(copy, env_lst->value, ft_strlen(env_lst->value));
			ptr = copy;
			break ;
		}
		env_lst = env_lst->next;
	}
	if (cmd_handler2(ptr, args) == NULL)
		printf("minishell: %s: not found...\n", args[0]);
}

/*
** For TESTING only
*/

void execArgsPiped(t_cmd *cmd_lst) 
{ 
    // 0 is read end, 1 is write end 
    int pipefd[2];  
    pid_t p1, p2; 
  
    if (pipe(pipefd) < 0) { 
        printf("\nPipe could not be initialized"); 
        return; 
    } 
    p1 = fork(); 
    if (p1 < 0) { 
        printf("\nCould not fork"); 
        return; 
    } 
  
    if (p1 == 0) { 
        // Child 1 executing.. 
        // It only needs to write at the write end 
        close(pipefd[0]); 
        dup2(pipefd[1], STDOUT_FILENO); 
        close(pipefd[1]); 
  
        if (execvp(cmd_lst->args[0], cmd_lst->args) < 0) { 
            printf("\nCould not execute command 1.."); 
            exit(0); 
        } 
    } else { 
        // Parent executing 
        p2 = fork(); 
 
        if (p2 < 0) { 
            printf("\nCould not fork"); 
            return; 
        } 
  
        // Child 2 executing.. 
        // It only needs to read at the read end 
        if (p2 == 0) { 
            close(pipefd[1]); 
            dup2(pipefd[0], STDIN_FILENO); 
            close(pipefd[0]); 
			cmd_lst = cmd_lst->next;
            if (execvp(cmd_lst->args[0], cmd_lst->args) < 0) { 
                printf("\nCould not execute command 2.."); 
                exit(0); 
            } 
        } else { 
            // parent executing, waiting for two children 
            wait(NULL); 
            wait(NULL); 
        } 
    } 
} 
