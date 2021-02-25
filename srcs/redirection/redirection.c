# include "../../includes/msh.h"

void parse_redirection()
{
	return ;
}

void	redir(t_state *st, t_ast *token)
{
	close(st->fdout);
	if (token->value[0] == '>')
	{
		token = token->right;
		st->fdout = open(token->value, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	}
	else
	{
		st->fdout = open(token->value, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
	}
	if (st->fdout == -1)
	{
		ft_putstr_fd("minishell: ", STDERR);
		ft_putstr_fd(token->value, STDERR);
		ft_putendl_fd(": No such file or directory", STDERR);
		g_sig.exit_status = 1;
		return ;
	}
	dup2(st->fdout, STDOUT);
}

void	input(t_state *st, t_ast *token)
{
	close(st->fdin);
	st->fdin = open(token->value, O_RDONLY, S_IRWXU);
	if (st->fdin == -1)
	{
		ft_putstr_fd("minishell: ", STDERR);
		ft_putstr_fd(token->value, STDERR);
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