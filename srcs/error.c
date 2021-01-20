#include "../includes/msh.h"

void	error_cases(int errnum, char *cmd, char *arg)
{
	ft_printf("bash: %s: %s: %s\n", cmd, arg, strerror(errnum));
}
