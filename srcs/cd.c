#include "msh.h"

/*
** Move to targeted directory
*/

char    *path_finding(void)
{
    char    *buf;

    if (!(buf = ft_calloc(1024, sizeof(char))))
        return (malloc(0));
    getcwd(buf, 1024 * sizeof(char));
    return (buf);
}

void    cpy_path(char *path, char *cur_path, char *dir)
{
    int i;
    int j;

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

int     main(int argc, char **argv)
{
    char    *path;
    char    *cur_path;

    cur_path = path_finding();
    ft_printf("%s\n%s\n", argv[1], cur_path);
    if (!(path = ft_calloc(1 + ft_strlen(cur_path) + 
        ft_strlen (argv[1]), sizeof(char))))
        return (EXIT_FAILURE);
    cpy_path(path, cur_path, argv[1]);
 //   ft_printf("%s\n%s\n%s\n", argv[1], cur_path, path);
    chdir(path);
    free (path);
    free(cur_path);
    return (EXIT_SUCCESS);
}