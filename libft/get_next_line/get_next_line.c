/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <jonny@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 13:30:06 by jonny             #+#    #+#             */
/*   Updated: 2021/01/05 17:14:59 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*check_lastline(char *str)
{
	int		i;
	int		len;
	char	*tmp;

	i = 0;
	while (str[i])
		i++;
	tmp = ft_substr(str, 0, ft_strlen(str));
	len = i;
	while (str[len] != '\0')
		len++;
	del(&str);
	str = ft_substr(tmp, (i + 1), len);
	del(&tmp);
	return (str);
}

char	*check_newline(char *str)
{
	int		i;
	int		len;
	char	*tmp;

	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	tmp = ft_substr(str, 0, ft_strlen(str));
	len = ft_strlen(tmp);
	if (str[i] == '\n')
	{
		del(&str);
		str = ft_substr(tmp, (i + 1), (len - i));
	}
	del(&tmp);
	return (str);
}

char	*add_line(char *str, char **line)
{
	int	len;

	len = 0;
	while (str[len] != '\0' && str[len] != '\n')
		len++;
	*line = ft_substr(str, 0, len);
	return (*line);
}

char	*join_buffer(char **line, char **s1, char *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	str = malloc(sizeof(char) * (ft_strlen(*s1) + ft_strlen(s2) + 1));
	if (str == NULL || s1 == NULL || s2 == NULL)
		return (NULL);
	while ((*s1)[i])
	{
		str[j++] = (*s1)[i];
		i++;
	}
	i = 0;
	while (s2[i])
	{
		str[j++] = s2[i];
		i++;
	}
	str[j] = '\0';
	del(s1);
	(*s1) = str;
	add_line(str, line);
	return (str);
}

/*
** get_next_line
**  1. check the conditions of fd, line and initialize s[fd] to 0 if NULL
** 	while there is something to read:
**  2. put a zero after the last char read in the buffer
**  then call the function join_buffer
**  3. check if s[fd] is not NULL and if there is a \n in s[fd]
**   3.1. call check_newline and resize the line up to the first \n occured
**  4. check if EOF is reached and s[fd] is equals to \0 and there is no \n
**  that means we reach the last line and call check_lastline
*/

int	get_next_line(int fd, char **line)
{
	static char	*s[FOPEN_MAX];
	static int	ret = 0;
	char		buf[BUFFER_SIZE + 1];

	if (init_gnl(&s[fd], fd, line) == -1)
		return (-1);
	while (ret >= 0)
	{
		ret = read(fd, buf, BUFFER_SIZE);
		buf[ret] = '\0';
		join_buffer(line, &s[fd], buf);
		if (s[fd] && ft_strchr(s[fd], '\n') != 0)
		{
			s[fd] = check_newline(s[fd]);
			return (1);
		}
		if (ret == 0 && (s[fd] == 0 || !ft_strchr(s[fd], '\n')))
		{
			s[fd] = check_lastline(s[fd]);
			del(&s[fd]);
			return (0);
		}
		del(line);
	}
	return (-1);
}
