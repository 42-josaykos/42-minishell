/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 13:02:43 by jonny             #+#    #+#             */
/*   Updated: 2021/03/16 18:59:54 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/msh.h"

/*
** Implementation of strsep
** $ man strsep
*/

char 	*ft_strsep(char **stringp, const char *delim)
{
	int		i;
	int		j;
	char	*tmp;

	tmp = *stringp;
	if (*stringp == NULL)
		return (NULL);
	i = 0;
	while (tmp[i])
	{
		j = 0;
		while (delim[j])
		{
			if (tmp[i] == delim[j])
			{
				tmp[i] = '\0';
				*stringp += (i + 1);
				return (tmp);
			}
			j++;
		}
		i++;
	}
	*stringp = NULL;
	return (tmp);
}

int	ft_readline2(char *tmp, char **str)
{
	int		len;

	len = ft_strlen(tmp);
	if (tmp[0] != 0 && tmp[len - 1] == '\n')
	{
		*str = ft_calloc(len + 1, sizeof(char));
		ft_strlcpy(*str, tmp, len + 1);
		return (1);
	}
	return (0);
}

void	check_buffer_overflow(char *buf, char *tmp)
{
	if (buf[BUF_SIZE - 1] != 0)
	{
		error_syntax(&buf[BUF_SIZE - 1]);
		ft_bzero(buf, BUF_SIZE);
		ft_strlcpy(buf, "\0", BUF_SIZE);
	}
	ft_strlcat(tmp, buf, BUF_SIZE);
}

void	print_prompt(char *prompt, char *color)
{
	ft_putstr_fd(color, STDERR);
	ft_putstr_fd(prompt, STDERR);
	ft_putstr_fd(RESET, STDERR);
}

char	*ft_readline(t_state *st, t_env *env_lst, char *prompt)
{
	char	*str;
	char	buf[BUF_SIZE];
	char	tmp[BUF_SIZE];
	int		ret;

	(void)st;
	(void)env_lst;
	ret = 0;
	str = NULL;
	ft_bzero(tmp, BUF_SIZE);
	st->termcap = tputs(tgetstr("ku", NULL), 1, ft_putchar);
	print_prompt(prompt, GREEN);
	init_termcap(st, env_lst);
	while (1)
	{
		ft_bzero(buf, BUF_SIZE);
		ret = read(0, buf, BUF_SIZE);
		if (ret == 0 && !ft_strlen(tmp))
			return (NULL);
		else if (!ft_strncmp(buf, "\e[A", 3))
		{
			ft_putstr_fd("arrow up catched !\n", 2);
			tcsetattr(STDIN_FILENO, TCSAFLUSH, &st->termios_backup);
		}
		else
		{
			check_buffer_overflow(buf, tmp);
			if (ft_readline2(tmp, &str))
				break ;
		}
	}
	return (str);
}
