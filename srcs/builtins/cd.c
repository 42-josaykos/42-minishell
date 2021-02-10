#include "../../includes/msh.h"

/*
** Move to targeted directory
*/

int	cd(char *arg, t_env *env_lst)
{
	int		errnum;
	int		ret;
	char	*str;
	char	tmp[BUF_SIZE];

	str = arg;
	if (arg && arg[0] == '-')
		str = get_env(env_lst, "OLDPWD");
	if (!arg || arg[0] == '~')
	{
		str = get_env(env_lst, "HOME");
		if (str == NULL || !ft_strlen(str))
			return (EXIT_SUCCESS);
	}
	getcwd(tmp, BUF_SIZE);
	ret = chdir(str);
	errnum = errno;
	export_env(&env_lst, "OLDPWD", tmp);
	if (ret == 0)
		return (EXIT_SUCCESS);
	error_cases(errnum, "cd", str);
	return (EXIT_FAILURE);
}
