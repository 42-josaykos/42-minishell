#include "msh.h"

/*
** Move to targeted directory
*/

int	cd(char *arg)
{
	int	ret;
	int	errnum;

	if (!arg || arg[0] == '~')
	{
		ret = chdir("/home/alpascal");
		errnum = errno;
		if (ret == 0)
			return (EXIT_SUCCESS);
		error_cases(errnum, "cd", arg);
		return (errnum);
	}
	ret = chdir(arg);
	errnum = errno;
	if (ret == 0)
		return (EXIT_SUCCESS);
	error_cases(errnum, "cd", arg);
	return (errnum);
}
