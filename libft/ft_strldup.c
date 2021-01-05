/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strldup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonny <jonny@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 17:54:20 by jonny             #+#    #+#             */
/*   Updated: 2021/01/05 16:02:50 by jonny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strldup(int len, const char *s1)
{
	int		i;
	char	*cpy;

	i = 0;
	cpy = (char *)ft_calloc(len + 1, sizeof(char));
	if (!cpy)
		return (NULL);
	while (s1[i])
	{
		cpy[i] = s1[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}
