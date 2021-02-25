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
	if (has_redirection(args))
	{
		while (*args[0] != '>')
			args++;
		redir(st, args);
	}
	return ;
}

/*
** Redirect stdout
*/

void	redir(t_state *st, char **args)
{
	ft_close(st->fdout);
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
}

/*
** arg as input
*/

void	input(t_state *st, char **args)
{
	ft_close(st->fdin);
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
