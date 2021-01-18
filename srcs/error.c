#include "msh.h"

void	error_cases(int errnum, char *cmd, char *arg)
{
	if (errnum == 2)
		printf("%s: %s: No such file or directory", cmd, arg);
	else if (errnum == 12)
		printf("%s: %s: Out of memory", cmd, arg);
	else if (errnum == 13)
		printf("%s: %s: Permission denied", cmd, arg);
	else if (errnum == 14)
		printf("%s: %s: Bad address", cmd, arg);
	else if (errnum == 20)
		printf("%s: %s: Not a directory", cmd, arg);
	else if (errnum == 36)
		printf("%s: %s: File name too long", cmd, arg);
	else if (errnum == 40)
		printf("%s: %s: Too many symbolic links encountered", cmd, arg);
	else if (errnum == 121)
		printf("%s: %s: Remote I/O error", cmd, arg);
}
