/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josaykos <josaykos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 11:27:42 by josaykos          #+#    #+#             */
/*   Updated: 2019/12/05 14:22:08 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dst;
	size_t	i;
	size_t	s_len;

	i = 0;
	if (s)
	{
		if (ft_strlen((char*)s) <= start)
			return (ft_strdup(""));
		s_len = ft_strlen((char*)s);
		if ((dst = (char*)ft_calloc(len + 1, sizeof(*dst))) == NULL)
			return (NULL);
		if (start < s_len)
		{
			while (i < len && s[start])
				dst[i++] = s[start++];
			return (dst);
		}
	}
	return (NULL);
}
