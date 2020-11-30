/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josaykos <josaykos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 10:51:47 by josaykos          #+#    #+#             */
/*   Updated: 2019/11/20 10:54:20 by josaykos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char *ret;

	ret = (char*)s;
	while (*ret != (char)c)
	{
		if (*ret == '\0')
			return (NULL);
		ret++;
	}
	return (ret);
}
