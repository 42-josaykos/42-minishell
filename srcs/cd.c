#include "msh.h"

/*
** Move to targeted directory
*/

int	cd(char *arg)
{
	int	errnum;
	int ret;

	if (!arg || arg[0] == '~')
	{
		ret = chdir("/home/alpascal");
		errnum = errno;
		if (ret == 0)
			return (EXIT_SUCCESS);
		error_cases(errnum, "cd", arg);
		return (EXIT_FAILURE);
	}
	ret =chdir(arg);
	errnum = errno;
	if (ret == 0)
		return (EXIT_SUCCESS);
	error_cases(errnum, "cd", arg);
	return (EXIT_FAILURE);
}
