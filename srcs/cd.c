#include "msh.h"

/*
** Move to targeted directory
*/

char	*path_finding(void)
{
	char	*buf;

	buf = ft_calloc(1024, sizeof(char));
	if (!buf)
		return (malloc(0));
	getcwd(buf, 1024 * sizeof(char));
	return (buf);
}

void	cpy_path(char *path, char *cur_path, char *dir)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cur_path[j])
		path[i++] = cur_path[j++];
	j = 0;
	path[i++] = '/';
	while (dir[j])
		path[i++] = dir[j++];
	path[i] = 0;
}

int	cd(char *arg)
{
	char	*path;
	char	*cur_path;

	cur_path = path_finding();
	path = ft_calloc(2 + ft_strlen(cur_path) + ft_strlen(arg), sizeof(char));
	if (!path)
		return (EXIT_FAILURE);
	cpy_path(path, cur_path, arg);
	chdir(path);
	free (path);
	free(cur_path);
	return (EXIT_SUCCESS);
}
