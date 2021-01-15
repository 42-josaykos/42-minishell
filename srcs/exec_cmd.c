/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <jonny@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 12:21:20 by jonny             #+#    #+#             */
/*   Updated: 2021/01/15 16:52:36 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"
#include <unistd.h>

/*
** Create a child process and execute the command in it. Parent process waits
** the child process to finish. read_path() reads the PATH and put it in the
** filepath[MAXCHAR] buffer. We add the filename to the path with ft_strcat()
*/

void	exec_cmd(char *filepath)
{
	char	*args[2];
	pid_t	p1;

	args[0] = filepath;
	args[1] = NULL;
	if (file_exists(args[0]) != 0)
		ft_printf("Command doesn't exist in PATH.\n");
	p1 = fork();
	if (p1 < 0)
	{
		ft_printf("Cannot execute child process.\n");
		exit(-1);
	}
	if (p1 == 0)
	{
		execve(args[0], args, NULL);
		exit(0);
	}
	wait(NULL);
}

void	cmd_handler(t_env *env_lst, char *input)
{
	char	filepath[MAXCHAR];

	while (env_lst)
	{
		if (ft_strncmp(env_lst->key, "path", 4) == 0)
		{
			read_path(env_lst, filepath);
			ft_strcat(filepath, input);
			if (file_exists(filepath) == 0)
			{
				exec_cmd(filepath);
				break ;
			}
		}
		env_lst = env_lst->next;
	}
	if (env_lst == NULL)
	{
		printf("minishell: %s: not found. Try in system shell...\n", input);
		exec_syscmd(input);
	}
}

/*
** Execute system command. system() function is not allowed in the subject !
** For debug only.
*/

void	exec_syscmd(char *input)
{
	pid_t	p1;

	p1 = fork();
	if (p1 < 0)
	{
		ft_printf("Cannot execute child process.\n");
		exit(-1);
	}
	if (p1 == 0)
	{
		system(input);
		exit(0);
	}
	wait(NULL);
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