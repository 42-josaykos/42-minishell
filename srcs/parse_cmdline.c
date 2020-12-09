#include "msh.h"

int parse_cmdline(char *input)
{
	int i;
	char *cmds_list[5];

	i = 0;
	cmds_list[0] = "pwd";
	cmds_list[1] = "echo";
	cmds_list[2] = NULL;
	if (ft_strncmp(input, "exit", 4) == 0)
		return (1);
	else if (ft_strlen(input) != 0)
	{
		while (cmds_list[i])
		{
			if (ft_strncmp(input, cmds_list[i], ft_strlen(cmds_list[i])) == 0)
				return (2);
			i++;
		}
		ft_printf("msh: %s: command not found\n", input);
	}
	return (0);
}
