/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josaykos <josaykos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 18:06:07 by josaykos          #+#    #+#             */
/*   Updated: 2019/11/09 11:05:58 by josaykos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	size_t				i;
	unsigned char		*ptr_dest;
	unsigned char		*ptr_src;

	i = 0;
	ptr_dest = (unsigned char*)dest;
	ptr_src = (unsigned char *)src;
	while (i < n)
	{
		if (ptr_src[i] == (unsigned char)c)
		{
			ptr_dest[i] = ptr_src[i];
			ptr_dest += (i + 1);
			return (ptr_dest);
		}
		else
			ptr_dest[i] = ptr_src[i];
		i++;
	}
	return (NULL);
}
