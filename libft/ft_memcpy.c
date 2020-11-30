/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josaykos <josaykos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 14:53:31 by josaykos          #+#    #+#             */
/*   Updated: 2019/11/20 10:41:20 by josaykos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t i;

	i = 0;
	if (!n || src == dest)
		return (dest);
	while (i < n)
	{
		*(char*)dest = *(char*)src;
		dest++;
		src++;
		i++;
	}
	return (dest - i);
}
