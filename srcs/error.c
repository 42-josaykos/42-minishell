#include "msh.h"

void	error_cases(int errnum, char *cmd, char *arg)
{
	if (errnum == 2)
		ft_printf("%s: %s: No such file or directory\n", cmd, arg);
	else if (errnum == 12)
		ft_printf("%s: %s: Out of memory\n", cmd, arg);
	else if (errnum == 13)
		ft_printf("%s: %s: Permission denied\n", cmd, arg);
	else if (errnum == 14)
		ft_printf("%s: %s: Bad address\n", cmd, arg);
	else if (errnum == 20)
		ft_printf("%s: %s: Not a directory\n", cmd, arg);
	else if (errnum == 36)
		ft_printf("%s: %s: File name too long\n", cmd, arg);
	else if (errnum == 40)
		ft_printf("%s: %s: Too many symbolic links encountered\n", cmd, arg);
	else if (errnum == 121)
		ft_printf("%s: %s: Remote I/O error\n", cmd, arg);
}
