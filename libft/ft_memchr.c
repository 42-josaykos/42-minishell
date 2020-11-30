/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josaykos <josaykos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 13:58:28 by josaykos          #+#    #+#             */
/*   Updated: 2019/11/20 10:27:56 by josaykos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	const char		*ptr_str;
	unsigned int	i;

	ptr_str = str;
	i = 0;
	while (i < n)
	{
		if (ptr_str[i] == c)
		{
			ptr_str += i;
			return ((char*)ptr_str);
		}
		i++;
	}
	return (NULL);
}
