/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 10:51:47 by josaykos          #+#    #+#             */
/*   Updated: 2021/02/25 10:36:56 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*ret;

	ret = (char *)s;
	while (*ret != (char)c)
	{
		if (*ret == '\0')
			return (NULL);
		ret++;
	}
	return (ret);
}
