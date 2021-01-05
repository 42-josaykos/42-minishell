/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <jonny@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 12:01:01 by josaykos          #+#    #+#             */
/*   Updated: 2021/01/05 16:01:06 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	j = 0;
	while (dest[j] && j < size)
		j++;
	i = j;
	while (src[j - i] && j + 1 < size)
	{
		dest[j] = src[j - i];
		j++;
	}
	if (i < size)
		dest[j] = '\0';
	return (i + ft_strlen(src));
}
