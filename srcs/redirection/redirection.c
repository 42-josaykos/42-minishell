# include "../../includes/msh.h"

void	input(t_state *st, char **args);
void	redir(t_state *st, char **args);

static bool	has_redirection(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (args[i][0] == '>' || args[i][0] == '<'
			|| !ft_strncmp(args[i], ">>", 3))
			return (true);
		i++;
	}
	return (false);
}

void parse_redirection(t_state *st, char **args)
{
	char *buffer[BUF_SIZE];
	int i = 0;
	int pos = 0;

	if (has_redirection(args))
	{
		ft_bzero(buffer, BUF_SIZE);
		while (args[i])
		{
			buffer[i] = ft_strdup(args[i]);
			i++;
		}
		st->redir = 1;
		while (args[pos][0] != '>')
			pos++;
		redir(st, args + pos);
		i = 0;
		while (args[i])
		{
			free(args[i]);
			args[i] = NULL;
			i++;
		}
		i = 0;
		while (buffer[i])
		{
			if (i != pos && i != pos + 1)
			{
				*args = ft_strdup(buffer[i]);
				args++;
			}
			i++;
		}
		i = 0;
		while (buffer[i])
		{
			free(buffer[i]);
			i++;
		}
	}
	return ;
}

/*
** Redirect stdout. [cmd] (> [new_fd is output]). (> [new_fd is ouput]) [cmd].
*/

void	redir(t_state *st, char **args)
{
	if (*args[0] == '>')
	{
		args++;
		st->fdout = open(*args, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	}
	else if (!ft_strncmp(*args, ">>", 3))
	{
		args++;
		st->fdout = open(*args, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
	}
	if (st->fdout == -1)
	{
		ft_putstr_fd("minishell: ", STDERR);
		ft_putstr_fd(*args, STDERR);
		ft_putendl_fd(": No such file or directory", STDERR);
		g_sig.exit_status = 1;
		return ;
	}
	dup2(st->fdout, STDOUT);
	ft_close(st->fdout);
}

/*
** arg as input `[cmd] < [input]`
*/

void	input(t_state *st, char **args)
{
	st->fdin = open(*args, O_RDONLY, S_IRWXU);
	if (st->fdin == -1)
	{
		ft_putstr_fd("minishell: ", STDERR);
		ft_putstr_fd(*args, STDERR);
		ft_putendl_fd(": No such file or directory", STDERR);
		g_sig.exit_status = 1;
		return ;
	}
	dup2(st->fdin, STDIN);
	ft_close(st->fdin);
}

void    init_fds(t_state **st)
{
    (*st)->fdin = -1;
    (*st)->fdout = -1;
}

void	ft_close(int fd)
{
	if (fd > 0)
		close(fd);
}

void	reset_std(t_state *st)
{
	dup2(st->in, STDIN);
	dup2(st->out, STDOUT);
}

void	close_fds(t_state *st)
{
	ft_close(st->fdin);
	ft_close(st->fdout);
}
