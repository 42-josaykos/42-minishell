/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 11:39:29 by josaykos          #+#    #+#             */
/*   Updated: 2021/02/25 10:35:20 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	if (dest == (char *)src)
		return (dest);
	if (dest < src)
		return (ft_memcpy(dest, src, n));
	else
	{
		while (n)
		{
			((char *)dest)[n - 1] = ((char *)src)[n - 1];
			n--;
		}
	}
	return (dest);
}
