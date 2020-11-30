/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 17:54:46 by jonny             #+#    #+#             */
/*   Updated: 2019/11/14 13:39:45 by josaykos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t n)
{
	size_t i;
	size_t j;

	if (*to_find == '\0')
		return ((char*)str);
	i = 0;
	while (i < n && str[i] != '\0')
	{
		j = 0;
		while (to_find[j] != '\0')
		{
			if (i + j >= n || str[i + j] != to_find[j])
				break ;
			j++;
		}
		if (to_find[j] == '\0')
			return ((char*)(str + i));
		i++;
	}
	return (0);
}
