#include "msh.h"

/*
** Move to targeted directory
*/

int	cd(char *arg, t_env *env_lst)
{
	int		errnum;
	int		ret;
	char	*str;
	char	tmp[MAXCHAR];

	str = arg;
	if (arg && arg[0] == '-')
		str = get_env(env_lst, "OLDPWD");
	if (!arg || arg[0] == '~')
		str = get_env(env_lst, "HOME");
	getcwd(tmp, MAXCHAR);
	ret = chdir(str);
	errnum = errno;
	export_env(&env_lst, "OLDPWD", tmp);
	if (ret == 0)
		return (EXIT_SUCCESS);
	error_cases(errnum, "cd", str);
	return (EXIT_FAILURE);
}
