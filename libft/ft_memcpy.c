/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 14:53:31 by josaykos          #+#    #+#             */
/*   Updated: 2021/02/25 10:35:08 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (!n || src == dest)
		return (dest);
	while (i < n)
	{
		*(char *)dest = *(char *)src;
		dest++;
		src++;
		i++;
	}
	return (dest - i);
}
