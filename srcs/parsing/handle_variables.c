/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 11:17:39 by jonny             #+#    #+#             */
/*   Updated: 2021/06/01 12:34:21 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/msh.h"

char	*ft_strsep_var(char **stringp, const char *delim)
{
	int		i;
	int		j;
	char	*tmp;

	tmp = *stringp;
	i = 0;
	while (tmp[i])
	{
		j = 0;
		while (delim[j])
		{
			if (tmp[i] == delim[j])
			{
				tmp = ft_substr(*stringp, 0, i);
				(*stringp) += i;
				return (tmp);
			}
			j++;
		}
		i++;
	}
	tmp = ft_strdup(*stringp);
	*stringp = NULL;
	return (tmp);
}

int	have_whitespaces(char *buf)
{
	int	i;

	i = 0;
	while (buf[i])
	{
		if (ft_isblank(buf[i]))
			return (1);
		i++;
	}
	return (0);
}

void	expand_var(char *buf, char *tmp, t_env *env_lst, t_ast **token)
{
	char	*ptr;
	char	*value;
	t_ast	*vars;

	(void)buf;
	ptr = NULL;
	ptr = ft_strsep_var(&tmp, "/=");
	value = get_env(env_lst, ptr);
	if (ptr)
		free(ptr);
	if (value)
	{
		if (have_whitespaces(value))
		{
			vars = parse_args(value);
			if (!(*token)->right)
			{
				token_lst_remove(token);
				(*token) = vars;
				return ;
			}
			while (vars->right)
				vars = vars->right;
			token_lst_remove(token);
			vars->right = *token;
			(*token)->left = vars;
			while ((*token)->left)
				*token = (*token)->left;
		}
		else
		{
			free((*token)->value);
			(*token)->value = ft_strdup(value);
			(*token)->type = ARG;
		}
	}
}

void	handle_variables(char *buf, t_ast **token, t_env *env_lst,
		t_ast **new_tkn)
{
	char	tmp[BUF_SIZE];
	char	*nbr;

	(void)new_tkn;
	ft_bzero(tmp, BUF_SIZE);
	if ((*token)->type == VAR)
	{
		ft_strlcpy(tmp, (*token)->value, ft_strlen((*token)->value) + 1);
		expand_var(buf, tmp, env_lst, token);
		if ((*token)->value)
		{
			if (have_whitespaces((*token)->value))
				return ;
			if ((*token) && (*token)->type != VAR)
				ft_strcat(buf, (*token)->value);
		}
	}
	else if ((*token)->type == QUEST)
	{
		if (g_sig.dollar_quote)
		{
			nbr = ft_itoa(g_sig.exit_status);
			ft_strcat(buf, nbr);
			free(nbr);
		}
		else
			ft_strcat(buf, (*token)->value);
	}
	g_sig.dollar_quote = false;
}
