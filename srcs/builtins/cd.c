/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 16:48:24 by jonny             #+#    #+#             */
/*   Updated: 2021/05/25 12:36:14 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/msh.h"

/*
** Move to targeted directory
*/

int	error_env(char *arg)
{
	char	*env;

	g_sig.exit_status = 1;
	env = "HOME";
	if (arg && !ft_strncmp(arg, "-", 2))
		env = "OLDPWD";
	ft_putstr_fd("msh: ", STDERR);
	ft_putstr_fd("cd", STDERR);
	ft_putstr_fd(": ", STDERR);
	ft_putstr_fd(env, STDERR);
	ft_putstr_fd(" not set", STDERR);
	ft_putstr_fd("\n", STDERR);
	return (1);
}

char	*cd_set_path(char *arg, t_env *env_lst)
{
	char	*str;

	str = arg;
	if (!arg || !ft_strncmp(arg, "~", 2))
		str = get_env(env_lst, "HOME");
	else if (arg && !ft_strncmp(arg, "-", 2))
	{
		str = get_env(env_lst, "OLDPWD");
		if (str)
			ft_putendl_fd(str, STDOUT);
	}
	return (str);
}

int	cd(char *arg, t_env *env_lst)
{
	int		errnum;
	int		ret;
	char	*str;
	char	tmp[BUF_SIZE];

	ret = 0;
	str = cd_set_path(arg, env_lst);
	if (str == NULL)
		return (error_env(arg));
	getcwd(tmp, BUF_SIZE);
	if (str[0] != '\0')
		ret = chdir(str);
	errnum = errno;
	if (!ret)
		export_env(&env_lst, ft_strdup("OLDPWD"), ft_strdup(tmp));
	if (ret == 0)
		return (EXIT_SUCCESS);
	error_cases(errnum, "cd", str);
	return (EXIT_FAILURE);
}
