/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josaykos <josaykos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 14:11:53 by josaykos          #+#    #+#             */
/*   Updated: 2019/11/20 11:34:13 by josaykos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_inset(char ch, char const *charset)
{
	int i;

	i = 0;
	while (charset[i])
	{
		if (ch == charset[i])
			return (1);
		i++;
	}
	return (0);
}

char			*ft_strtrim(char const *s1, char const *set)
{
	char	*copy;
	char	*final_str;
	int		len;

	len = 0;
	if (s1 && set)
	{
		if (!(copy = ft_strdup(s1)))
			return (0);
		while (ft_inset(*copy, set) == 1)
			copy++;
		len = ft_strlen(copy);
		while (len - 1 >= 0)
		{
			if (ft_inset(copy[len - 1], set) == 0)
				break ;
			else
				copy[len - 1] = '\0';
			len--;
		}
		final_str = ft_strdup(copy);
		return (final_str);
	}
	return (NULL);
}
